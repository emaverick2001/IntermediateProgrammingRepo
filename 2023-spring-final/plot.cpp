// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include <cassert>
#include "plot.h"

Plot::Plot() {
  // Initialize the bounds to the default values of 0
  bound_ = Bounds();
  width_ = 0;
  height_ = 0; 
}

Plot::~Plot() {
  // Dynamically deallocate all the functions and fills
  for (std::size_t i = 0; i < functions_.size(); i++) {
    delete functions_[i];
  }

  for (std::size_t i = 0; i < fills_.size(); i++) {
    delete fills_[i];
  }
}

// Adds color to plot
void Plot::add_color(const std::string& name, const Color& color) {
    // Prevents more than one Color directive for a function
    if (colors_.find(name) != colors_.end()) {
      throw PlotException("Color with the same name already exists");
    }
    colors_[name] = color;
}

// Checks if function has been added to plot 
bool Plot::has_function(const std::string &fn_name) const {
  for (std::vector<Function *>::const_iterator it = functions_.begin(); it != functions_.end(); ++it) {
    if ((*it)->get_name() == fn_name) {
      return true;
    }
  }
  return false;
}

