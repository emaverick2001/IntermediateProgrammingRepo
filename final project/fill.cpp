#include <cassert>
#include "fill.h" 
#include "func.h"
#include "color.h"


// nondefault constructor
Fill::Fill(const std::string funcname,const std::string funcname2 , const double opacity, const Color& color,
           const std::string type)
    : m_funcname(funcname), m_funcname2(funcname2), m_opacity(opacity), m_color(color), m_type(type) {}

// destructor
Fill::~Fill() {}

// copy constructor


Fill::Fill(const Fill& other)
    : m_funcname(other.m_funcname),
      m_funcname2(other.m_funcname2),
      m_opacity(other.m_opacity),
      m_color(other.m_color) {
}

// // assignment operator
// Fill& Fill::operator=(const Fill& other) {
//   if (this == &other) {
//     // Self-assignment check
//     return *this;
//   }

//   // Copy the values from the other object to this object
//   m_function1 = other.m_function1;
//   m_function2 = other.m_function2;
//   m_opacity = other.m_opacity;
//   m_color = other.m_color;

//   // Return a reference to this object
//   return *this;
// }

//commented out because already defined in .h file
// Color Fill::get_color() const{
//   return m_color;
// }

// double Fill::get_opacity() const{
//   return m_opacity;
// } 

std::string Fill::get_function1() const{
  return m_funcname;
}

std::string Fill::get_function2() const{
  return m_funcname2;
}

std::string Fill::get_fill_type() const{
  return m_type;
}

void Fill::set_color(Color &color){
  m_color = color;
}

void Fill::set_opacity(double &opacity){
  m_opacity = opacity;
}
