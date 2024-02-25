#include <iostream>
#include <cassert>
#include <memory>
#include <fstream> //delete
#include "exception.h"
#include "expr.h"
#include "renderer.h"
#include "plot.h"
#include "expr_parser.h"
#include "fill.h"
#include "bounds.h"
#include "color.h"
#include "func.h"
#include "image.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();

  // the unique_ptr will take care of deleting the Image object
  // if an exception is thrown
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();

  //1 render the fills
  //2 render the function
  //3 return the img

  float x_min = m_plot.getBounds().get_xmin();
  float x_max = m_plot.getBounds().get_xmax();
  float y_min = m_plot.getBounds().get_ymin();
  float y_max = m_plot.getBounds().get_ymax();

  float y_val = 0;
  float xj = 0;
  float yi = 0;
  float y_val2 = 0;
  // TODO: render the plot image
  //writing logic for fills functions
  std::map<std::string,Function*> map_new = m_plot.getfunctionsmap();

  std::vector<Fill*> fill_new = m_plot.getfills();
  
  for(std::vector<Fill*>::iterator it = fill_new.begin(); it != fill_new.end(); ++it){
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++){
        Fill* fill = *it;
        std::string function_name1 = fill->get_function1();
        std::string function_name2 = fill->get_function2();
        // Check if function exists
        // if (!m_plot.check_function_name_exists(function_name1) || !m_plot.check_function_name_exists(function_name2)) { 
        //   throw PlotException("Error: function name does not exist in plot");
        // }
        Function* f1 = m_plot.getfunction(function_name1);
        std::string directive_name = fill->get_fill_type();
        //find which point each pixel rep in x/y plane
        xj = x_min+((j*1.0)/width)*(x_max-x_min);
        yi = y_min+((height-1-(i*1.0))/height)*(y_max-y_min);
        y_val = f1->get_expr()->eval(xj);//get expression
        //pixel_row = height-1-(((y_val-y_min)/(y_max-y_min))*height);

        //need to check if fill area is valid
        if (fill->get_fill_type() == "FillAbove" && f1 != nullptr){
          if (yi > y_val){
            Color original_color = m_img->get_pixel(j, i);
            double alpha = fill->get_opacity();
            uint8_t r = std::floor((1 - alpha) * original_color.r + alpha * fill->get_color().r);
            uint8_t g = std::floor((1 - alpha) * original_color.g + alpha * fill->get_color().g);
            uint8_t b = std::floor((1 - alpha) * original_color.b + alpha * fill->get_color().b);
            Color blended_color;
            blended_color.setRval(r);
            blended_color.setGval(g);
            blended_color.setBval(b);
            m_img->set_pixel(j, i, blended_color);
          }
        }

        else if (fill->get_fill_type() == "FillBelow" && f1 != nullptr){
          if (yi < y_val){
            Color original_color = m_img->get_pixel(j, i);
            double alpha = fill->get_opacity();
            uint8_t r = std::floor((1 - alpha) * original_color.r + alpha * fill->get_color().r);
            uint8_t g = std::floor((1 - alpha) * original_color.g + alpha * fill->get_color().g);
            uint8_t b = std::floor((1 - alpha) * original_color.b + alpha * fill->get_color().b);
            Color blended_color;
            blended_color.setRval(r);
            blended_color.setGval(g);
            blended_color.setBval(b);
            m_img->set_pixel(j, i, blended_color);
          }
        }

        else if (fill->get_fill_type() == "FillBetween" && f1 != nullptr){
          Function* f2 = m_plot.getfunction(function_name2);
          if (f2 != nullptr){
            y_val2 = f2->get_expr()->eval(xj);//get expression
          }
          if ((yi < y_val && yi > y_val2) || (yi < y_val2 && yi > y_val)){
            Color original_color = m_img->get_pixel(j, i);
            double alpha = fill->get_opacity();
            uint8_t r = std::floor((1 - alpha) * original_color.r + alpha * fill->get_color().r);
            uint8_t g = std::floor((1 - alpha) * original_color.g + alpha * fill->get_color().g);
            uint8_t b = std::floor((1 - alpha) * original_color.b + alpha * fill->get_color().b);
            Color blended_color;
            blended_color.setRval(r);
            blended_color.setGval(g);
            blended_color.setBval(b);
            m_img->set_pixel(j, i, blended_color);
          }
        }

        
      }
   } 
  }

  //for plotting function
  for (std::map<std::string,Function*>::iterator it = map_new.begin(); it != map_new.end(); ++it){
    //get each functions color

    //use functions color that is specified
    Color func_color = it->second->get_color();


  const Expr* func_expr = it->second->get_expr();
  // Iterate through all columns (x-axis)
    for (int j = 0; j < width; ++j) {

      // Find the corresponding row (y-axis) for the current column
      int i = find_pixel_row(j, func_expr, x_min, x_max, y_min, y_max, width, height);

      // If the row is within the image height, set the pixel to the function's color
      if (i >= 0 && i < height) {
        draw_pixel(j, i, func_color);
        draw_pixel(j+1, i, func_color);
        draw_pixel(j-1, i, func_color);
        draw_pixel(j, i+1, func_color);
        draw_pixel(j, i-1, func_color);
      }
    }
  } 
  
  return img.release();
}

// TODO: implement private helper functions

// Calculates the pixel row using i = h - 1 - floor((y-y_min)/(y_max-y_min) * h), where y = f(x_min + (j/w) * (x_max - x_min))  
int Renderer::find_pixel_row(int j, const Expr *f, double x_min, double x_max, double y_min, double y_max, int width, int height) {
  double x = x_min + (j /static_cast<double>(width)) * (x_max - x_min);
  double y = f->eval(x);
  int i = height - 1 - std::floor(((y - y_min) / (y_max - y_min)) * height);
  return i;
}

// Helper function that draws a pixel of given color at the location given 
void Renderer::draw_pixel(int x, int y, Color &func_color) {
  // Get width and height 
  int width = m_img->get_width();
  int height = m_img->get_height();
  // Check that it is within image bounds and set pixel to that location
  if (x >= 0 && x < width && y >=0 && y < height) {
    m_img -> set_pixel(x, y, func_color);
  }
}

bool Renderer::isValidFill(const Fill* fill, double x, double y, std::string name1, std::string name2) {
  // Grab the first function and make sure that it is valid
  const Function* function1 = m_plot.getfunction(name1);
  if (function1 == nullptr) {
      return false;
  }
  // Get y-value of the function at point x
  double function1_value = function1->get_expr()->eval(x);

  // Check fill type and compare with y value based on type
  if (fill->get_fill_type() == "FillAbove") {
    return y >= function1_value;
  } else if (fill->get_fill_type() == "FillBelow") {
    return y <= function1_value;
  } else if (fill->get_fill_type() == "FillBetween") {
    const Function* function2 = m_plot.getfunction(name2);
    if (function2 == nullptr) {
      return false;
    }
    // Get y-value of function again
    double function2_value = function2->get_expr()->eval(x);
    return (y >= function1_value && y <= function2_value) || (y <= function1_value && y >= function2_value);
    }

  return false; // None of the conditions are met
}