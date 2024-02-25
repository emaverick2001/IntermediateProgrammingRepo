// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#include "func.h"

Function::Function() : m_name(""), m_expr(), m_color() {
}

Function::Function(const std::string &name, Expr *expr) : m_name(name), m_expr(expr){}

Function::~Function() {
  // TODO: deallocate objects if necessary 
}
