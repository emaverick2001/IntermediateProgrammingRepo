
// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "color.h"
#include "plot.h"
#include "func.h"

// Added enum class FillType to represent the type of fill: Above, Below, or Between
enum class FillType {ABOVE, BELOW, BETWEEN};

class Fill {
private:
  // Added private member variables to represent the fill type, the function names, the opacity, and color
  FillType fill_type_;
  std::string fn_name1_;
  std::string fn_name2_;
  double opacity_;
  Color color_;
  
public:
  // Added constructors for each fill type (above, below, between), account for FillAbove and FillBelow, then FillBetween
  Fill(FillType fill_type, const std::string& fn_name1, double opacity, const Color& color);
  Fill(FillType fill_type, const std::string& fn_name1, const std::string& fn_name2, double opacity, const Color& color);
  
  // Destructor 
  ~Fill();

  // Added appropriate member functions as getters
  FillType get_fill_type() const {return fill_type_;}
  const std::string& get_fn_name1() const {return fn_name1_;}
  const std::string& get_fn_name2() const {return fn_name2_;}
  double get_opacity() const {return opacity_;}
  const Color& get_color() const {return color_;}
};

#endif // FILL_H