// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include <cmath>
#include <stdexcept>
#include "exception.h"
#include "expr.h"

// Expr (base class)
Expr::Expr() {
}

// Destructor
Expr::~Expr() {
  // Deallocate child nodes (if any)
  for (size_t i = 0; i < children.size(); i++) {
    delete children[i];
  }
}

// Evaluates addition expressions 
double AddExpr::eval(double x) const {
  double result = 0.0;
  // Adds all the arguments that are provided 
  for (size_t i = 0; i < numChildren(); i++) {
    result += getChild(i)->eval(x);
  }
  return result;
}

// Evaluates subtraction expressions 
double SubExpr::eval(double x) const {
  // Checks to make sure there are exactly two argument expressions
  if (numChildren() != 2) {
    throw PlotException("Subtract expression requires exactly two operands");
  }
  // Subtracts both the provided arguments and returns the result
  return getChild(0)->eval(x) - getChild(1)->eval(x);
}

// Evaluates multiplication expressions 
double MultExpr::eval(double x) const {
  double result = 1.0;
  // Multiplies all the arguments that are provided 
  for (size_t i = 0; i < numChildren(); i++) {
    result *= getChild(i)->eval(x);
  }
  return result;
}

// Evaluates division expressions 
double DivExpr::eval(double x) const {
  // Checks to make sure there are exactly two argument expressions
  if (numChildren() != 2) {
    throw PlotException("Divide expression requires exactly two operands");
  }

  // Sets the denominator equal to the second argument
  double denominator = getChild(1)->eval(x);

  // Checks to make sure we are not dividing by zero and throws an exception if we are
  if (denominator == 0) {
    throw PlotException("Divide by zero error");
  }

  return getChild(0)->eval(x) / denominator;
}

// Represents the constant pi
double Pi::eval(double) const {
  return M_PI;
}

// Represents a constant number
double LiteralNumber::eval(double) const {
  return m_value;
}

// Evaluates sin expressions
double Sin::eval(double x) const {
  return std::sin(m_arg->eval(x));
}

void Sin::addChild(Expr* expr) {
  // Check to make sure only one argument is provided 
  if (m_arg != nullptr) {
    throw PlotException("Sin only takes one argument");
  }
  m_arg = expr;
}

// Evaluates cos expressions
double Cos::eval(double x) const {
  return std::cos(m_arg->eval(x));
}

void Cos::addChild(Expr* expr) {
  // Check to make sure only one argument is provided 
  if (m_arg != nullptr) {
    throw PlotException("Cos only takes one argument");
  }
  m_arg = expr;
}

