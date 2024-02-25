// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"
#include "color.h"

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

  // 1. fill the background
  // 2. render the functions
  // 3. render the fills
  // 4. return the image

  renderFills();
  renderFunctions();

  return img.release();
}

// Color blending function which utilizes formula provided C_blend = (1 - alpha) * C_orig + alpha * C_fill to blend the original color with the fill color
Color Renderer::color_blend(const Color& orig, const Color& fill, double alpha) {
  uint8_t r = std::floor((1 - alpha) * orig.r + alpha * fill.r);
  uint8_t g = std::floor((1 - alpha) * orig.g + alpha * fill.g);
  uint8_t b = std::floor((1 - alpha) * orig.b + alpha * fill.b);
  return Color(r, g, b);
}

/* Function that determines precise location of x/y coordinates for a pixel, which allows determination of if a point is above,below, or between functions
and decide if it should be filled. Uses formulas xj = x_min + (j/w) * (x_max - x_min), yi = y_min + ((h - 1 - i)/h) * (y_max - y_min) */
std::pair<double, double> Renderer::pixel_to_XY(int i, int j, double x_min, double x_max, double y_min, double y_max, int width, int height) {
  double x = x_min + (j/static_cast<double>(width)) * (x_max - x_min);
  double y = y_min + ((height - 1 - i)/static_cast<double>(height)) * (y_max - y_min);
  return std::make_pair(x, y);
}

// Calculates the pixel row. For column j, the row i is calculated by the formula provided: i = h - 1 - floor((y-y_min)/(y_max-y_min) * h), where y = f(x_min + (j/w) * (x_max - x_min))  
int Renderer::find_pixel_row(int j, const Expr *f, double x_min, double x_max, double y_min, double y_max, int width, int height) {
  double x = x_min + (j /static_cast<double>(width)) * (x_max - x_min);
  double y = f->eval(x);
  int i = height - 1 - std::floor(((y - y_min) / (y_max - y_min)) * height);
  return i;
}

// Returns pointer to the function with the given name or nullptr
const Function* Renderer::get_func_name(const std::string& name) {
    // Loop through the functions and if the name matches, get the name 
    for (const Function* func : m_plot.get_functions()) {
        if (func->get_name() == name) {
            return func;
        }
    }
    return nullptr;
}

// Checks if a given fill is valid for a point (x,y)
bool Renderer::is_valid_fill(const Fill* fill, double x, double y) {
  // Grab the first function and make sure that it is valid
  const Function* func1 = get_func_name(fill->get_fn_name1());
  if (func1 == nullptr) {
      return false;
  }
  // Get y-value of the function at point x
  double func1_value = func1->get_expr()->eval(x);

  // Check fill type and compare with y value based on type
  if (fill->get_fill_type() == FillType::ABOVE) {
    return y >= func1_value;
  } else if (fill->get_fill_type() == FillType::BELOW) {
    return y <= func1_value;
  } else if (fill->get_fill_type() == FillType::BETWEEN) {
    const Function* func2 = get_func_name(fill->get_fn_name2());
    if (func2 == nullptr) {
      return false;
    }
    // Get y-value of function again
    double func2_value = func2->get_expr()->eval(x);
    return (y >= func1_value && y <= func2_value) || (y <= func1_value && y >= func2_value);
    }

  return false; // None of the conditions are met
}

void Renderer::renderFills() { 
  // Grab width/height and plot bounds
  int width = m_img->get_width();
  int height = m_img->get_height();
  Bounds plot_bounds = m_plot.get_bound();
  double x_min = plot_bounds.get_xmin();
  double x_max = plot_bounds.get_xmax();
  double y_min = plot_bounds.get_ymin();
  double y_max = plot_bounds.get_ymax();

  // Loop through plot and pixels, while converting pixels to xy coords
  for (const Fill* fill : m_plot.get_fills()) {
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        std::pair<double, double> xy = pixel_to_XY(i, j, x_min, x_max, y_min, y_max, width, height);
        double x = xy.first;
        double y = xy.second;

        // Make sure the pixel is inside fill area 
        bool in_fill_area = is_valid_fill(fill, x, y);

        if (in_fill_area) {
          // Blend the fill color with the original color of pixel
          Color original_color = m_img->get_pixel(j, i);
          Color blended_color = color_blend(original_color, fill->get_color(), fill->get_opacity());
          m_img->set_pixel(j, i, blended_color);
        }
      }
    }
  }
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

void Renderer::renderFunctions() {
  int width = m_img->get_width();
  int height = m_img->get_height();
  Bounds plot_bounds = m_plot.get_bound();
  double x_min = plot_bounds.get_xmin();
  double x_max = plot_bounds.get_xmax();
  double y_min = plot_bounds.get_ymin();
  double y_max = plot_bounds.get_ymax();

  // Render each function in the plot
  for (const Function* func : m_plot.get_functions()) {
    // If a color value for the function was specified, use that color
    std::map<std::string, Color>::const_iterator func_color_iter = m_plot.get_colors().find(func->get_name());
    
    Color func_color(255, 255, 255);
    if (func_color_iter != m_plot.get_colors().end()) {
        func_color = func_color_iter->second;
    }
    const Expr* func_expr = func->get_expr();

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
}