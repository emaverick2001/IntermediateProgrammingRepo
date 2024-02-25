// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"
#include "color.h"

class Function {
private:
  // a function has a name and an expression computing its value (given x)
  std::string m_name;
  Expr *m_expr;
  Color m_color; 

  // value semantics prohibited
  Function(const Function &); //copy constructor
  Function &operator=(const Function &); //asignment operator

public:
  Function(); //creating a default constructor
  Function(const std::string &name, Expr *expr);
  ~Function();

  //getters
  std::string get_name() const { return m_name; }
  Expr *get_expr() const       { return m_expr; }
  Color get_color() const {return m_color; }
  
  void setColor(int rval,int gval,int bval) {
    m_color.setRval((unsigned int)rval);
    m_color.setGval((unsigned int)gval);
    m_color.setBval((unsigned int)bval);
  }

  
};

#endif // FUNC_H
