// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#include <cmath>
#include "exception.h"
#include "expr.h"

// Expr (base class)

Expr::Expr() {}

Expr::~Expr() {}

// TODO: implement member functions for derived classes

void Sin::addChild(Expr* expr) {
  // Check to make sure only one argument is provided 
  if (m_arg != nullptr) {
    throw PlotException("Error: sin takes one argument only");
  }
  m_arg = expr;
}

void Cos::addChild(Expr* expr) {
  // Check to make sure only one argument is provided 
  if (m_arg != nullptr) {
    throw PlotException("Error: cos takes one argument only");
  }
  m_arg = expr;
}

double Sin::eval(double x) const{
  return std::sin(m_arg->eval(x));
}

double Cos::eval(double x) const{
  return std::cos(m_arg->eval(x));
}

double Add::eval(double val) const{
  // Adds all the arguments stored in children vector
  // should work even though there are only 2 arguments
  double sum = 0; 
  for (size_t i = 0; i < numChildren(); i++) {
    sum += getChild(i)->eval(val);
  }
  return sum;
}

double Subtract::eval(double val) const{
  if (numChildren() != 2) {
    throw PlotException("Subtract expression requires exactly two operands");
  }
  return getChild(0)->eval(val) - getChild(1)->eval(val);
}


double Multiply::eval(double x) const {
  double result = 1.0;
  for (size_t i = 0; i < numChildren(); i++){
    result *= getChild(i)->eval(x);
  }
  return result;
}

double Divide::eval(double val) const {
  double num = getChild(0)->eval(val);
  double den = getChild(1)->eval(val);

if (numChildren() != 2) {
    throw PlotException("Divide expression requires exactly two operands");
  }

  if (den == 0){
    throw PlotException("Error: division by 0");
  }
  double result = num/den;
  return result;

}

