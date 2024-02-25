// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include <iostream>
#include <map>
#include <sstream>
#include <cstdint>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"

using std::string;
using std::istringstream;
using std::getline;

// Constructor of the Reader class
Reader::Reader() {
}

// Destructor of the Reader class
Reader::~Reader() {
}

// Helper function to validate function names in fill directives
void Reader::validate_function_names(const Plot &plot, const std::string &fn_name1, const std::string &fn_name2) {
  if (!plot.has_function(fn_name1)) {
    throw PlotException("Function '" + fn_name1 + "' not found in plot");
  }
  if (!fn_name2.empty() && !plot.has_function(fn_name2)) {
    throw PlotException("Function '" + fn_name2 + "' not found in plot");
  }
}


void Reader::read_input(std::istream &in, Plot &plot) {
  // Read plot input from in, add information to plot
  std::string line;
  // Read plot input from the input stream line by line
  while (std::getline(in, line)) {
    // Create a stringstream from the line and read first word as command 
    istringstream iss(line);
    string command;
    // Read the first word in the line as the command
    iss >> command;
    if (command == "Plot") {
      // Read the bound values for the plot
      double x_min, x_max, y_min, y_max;
       // Throw exception if unable to read arguments
      if(!(iss >> x_min >> y_min >> x_max >> y_max)) {
        throw PlotException("Failed to read bound values");
      }
      
      // Make sure bounds are valid 
      if (x_min >= x_max || y_min >= y_max) {
        throw PlotException("Invalid bounds");
      }
      // Set bounds of the plot 
      plot.set_bound(Bounds(x_min, x_max, y_min, y_max));

      // Get the image width and height 
      int width, height;
      // Throw exception if unable to read arguments
      if(!(iss >> width >> height)) {
        throw PlotException("Failed to image width and height");
      }

      int num_args;
       // Throw exception if there are too many arguments
      if (iss >> num_args) {
        throw PlotException("Too many arguments");
      }
      // Make sure image size is valid
      if (width <= 0 || height <= 0) {
        throw PlotException("Invalid number of arguments to Plot directive");
      }
      // Set the image width and height 
      plot.set_width(width);
      plot.set_height(height);
    } 
    else if (command == "Color") {
      // Read function name and color values 
      std::string fn_name;
      int r = -1, g = -1, b = -1;
      iss >> fn_name;
       // Check if it is a valid function name 
      validate_function_names(plot, fn_name, "");
       // Throw exception if unable to read arguments
      if (!(iss >> r >> g >> b)) {
        throw PlotException("Failed to read color values");
      }
      int num_args_1;
       // Throw exception if too many arguments are provided 
      if (iss >> num_args_1) {
        throw PlotException("Invalid number of arguments to Color directive");
      }
      // Check that the color values are valid
      if (r > 255 || g > 255 || b > 255) {
        throw PlotException("Invalid color");
      }
      else if (r < 0 || g < 0 || b < 0) {
        throw PlotException("Invalid color");
      }
      // Create a Color object from the color values
      Color color(r, g, b);
      // Add the color to the plot with the given function 
      plot.add_color(fn_name, color);
    }

   else if (command == "Function") {
      // Read function name and expression 
      string fn_name;
      string expr;
       // Throw exception if unable to read arguments
      if (!(iss >> fn_name)) {
        throw PlotException("Failed to read function name");
      }

      // Check if the function name is empty
      if (fn_name.empty()) {
        throw PlotException("Function name cannot be empty");
      }

      // Check if function name already exists 
      if (plot.has_function(fn_name)) {
        throw PlotException("Function already exists");
      }

      // Read expression from rest of line 
      getline(iss, expr);
      // Removes leading spaces and tabs, avoids core dump
      expr.erase(0, expr.find_first_not_of(" \t")); 
      std::istringstream expr_stream(expr);

      ExprParser parser;
      // Parse the expression and create a new Function object
      Function* function = new Function(fn_name, parser.parse(expr_stream));
      plot.add_function(function);
    }

   else if (command == "FillAbove" || command == "FillBelow" || command == "FillBetween") {
      // Define functions that are input through text and other variables
      std::string fn_name1;
      std::string fn_name2; // only used for FillBetween
      double opacity;
      int r, g, b;
      if (command == "FillBetween") {
         // Throw exception if unable to read arguments
        if (!(iss >> fn_name1 >> fn_name2 >> opacity >> r >> g >> b)) {
          throw PlotException("Failed to read FillBetween values");
        }
      } else {
         // Throw exception if unable to read arguments
        if (!(iss >> fn_name1 >> opacity >> r >> g >> b)) {
          throw PlotException("Failed to read FillAbove or FillBelow values");
        }
      }
       // Throw exception if too many arguments are provided
      int num_args_2;
      if (iss >> num_args_2) {
        throw PlotException("Invalid number of arguments to Fill directive");
      }
      // Check for errors after reading values like opacity and rgb 
      if (opacity < 0 || opacity > 1) {
        throw PlotException("Invalid opacity");
      }
      if (r > 255 || g > 255 || b > 255) {
        throw PlotException("Invalid color");
      }
      else if (r < 0 || g < 0 || b < 0) {
        throw PlotException("Invalid color");
      }
      Color color(r, g, b);
      // Check for fill type and fill the plot accordingly 
      if (command == "FillAbove") {
        // Throw exception if invalid function name provided
        validate_function_names(plot, fn_name1, "");
        Fill* fill = new Fill(FillType::ABOVE, fn_name1, opacity, color);
        plot.add_fill(fill);
      } else if (command == "FillBelow") {
        // Throw exception if invalid function name provided
        validate_function_names(plot, fn_name1, "");
        Fill* fill = new Fill(FillType::BELOW, fn_name1, opacity, color);
        plot.add_fill(fill);
      } else if (command == "FillBetween") {
        // Throw exception if invalid function name provided
        validate_function_names(plot, fn_name1, fn_name2);
        Fill* fill = new Fill(FillType::BETWEEN, fn_name1, fn_name2, opacity, color);
        plot.add_fill(fill);
      }
    } 
    else {
      // Invalid command case 
      throw PlotException("Invalid command");
    }
  }
}

