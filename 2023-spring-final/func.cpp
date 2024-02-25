// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include "func.h"

 // Constructor for function class that takes name and expression expr
Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr) {
}
  
Function::~Function() {
  // Deallocate the memory allocated for m_expr pointer
  delete m_expr;
}
