// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <cmath> 
#include "exception.h"

// Base expression class

class Expr {
private:
  // field(s) to store links to child Expr nodes
  std::vector<Expr*> children;

  // value semantics are prohibited
  Expr(const Expr &);
  Expr &operator=(const Expr &);

public:
  Expr();
  virtual ~Expr();

  virtual double eval(double value) const = 0;

  void addChild(Expr* child) { children.push_back(child); }
  Expr* getChild(size_t i) const { return children[i]; }
  size_t numChildren() const { return children.size(); }
};

// TODO: add derived expression classes

// X Node
class X : public Expr {
  public:
  X() {}
  double eval(double x) const override{return x;}
};

//Pi Node
class Pi : public Expr {
  public:
  Pi() {}
  double eval(double) const override{return M_PI;}
};

//Literal Node
class Literal : public Expr {
  private:
  double m_value;
  
  public:
  Literal(double literalval) : m_value(literalval) {}

  double eval(double) const override{return m_value;}
};

// Sin Node
class Sin : public Expr {
private:
  Expr *m_arg;

public:
  Sin(Expr *arg) : m_arg(arg) {}

  ~Sin() {
    delete m_arg;
  }

  virtual double eval(double x) const override;

  virtual void addChild(Expr* expr); 
};

// Cos Node
class Cos : public Expr {
  private:
    Expr* m_arg;

  public:
    Cos(Expr* arg) : m_arg(arg) {}

    ~Cos() {
      delete m_arg;
    }

  virtual double eval(double cosval) const override;

  virtual void addChild(Expr* expr); 
};

//Add Node
class Add : public Expr {
  public:
  Add() {}

  virtual ~Add() {}

  virtual double eval(double val) const override;
  
};

//Subtract Node
class Subtract : public Expr {
  public:
  Subtract() {}

  virtual ~Subtract() {}

  virtual double eval(double val) const override;
};

//Divide Node
class Divide : public Expr {
  public:
  Divide() {}

  virtual ~Divide() {}

  virtual double eval(double val) const override;
};

//Multiply Node
class Multiply : public Expr {
  public:
  Multiply() {}

  virtual ~Multiply() {}

  virtual double eval(double val) const override;
};

#endif // EXPR_H
