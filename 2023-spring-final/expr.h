#ifndef EXPR_H
#define EXPR_H

#include "exception.h"
#include <cmath>
#include <vector>

/**
 * @class Expr
 * @brief Base expression class representing mathematical expressions.
 */
class Expr {
private:
  // Field to store links to child Expr nodes
  std::vector<Expr*> children;

  // Disable value semantics
  Expr(const Expr &);
  Expr &operator=(const Expr &);

public:
  Expr();
  virtual ~Expr();

  /**
   * @brief Evaluate the expression with the given value of x.
   * @param x The value of x to evaluate the expression with.
   * @return The result of the evaluated expression.
   */
  virtual double eval(double x) const = 0;

  // Member functions for managing child expressions
  void addChild(Expr* child) { children.push_back(child); }
  Expr* getChild(size_t i) const { return children[i]; }
  size_t numChildren() const { return children.size(); }
};

/**
 * @class AddExpr
 * @brief Derived class representing addition expressions.
 */
class AddExpr : public Expr {
public:
  // Constructor
  AddExpr() {}

  // Destructor
  virtual ~AddExpr() {}

  // Evaluation function
  virtual double eval(double x) const;
};

/**
 * @class SubExpr
 * @brief Derived class representing subtraction expressions.
 */
class SubExpr : public Expr {
public:
  // Constructor
  SubExpr() {}

  // Destructor
  virtual ~SubExpr() {}

  // Evaluation function
  virtual double eval(double x) const;
};

/**
 * @class MultExpr
 * @brief Derived class representing multiplication expressions.
 */
class MultExpr : public Expr {
public:
  // Constructor
  MultExpr() {}

  // Destructor
  virtual ~MultExpr() {}

  // Evaluation function
  virtual double eval(double x) const;
};

/**
 * @class DivExpr
 * @brief Derived class representing division expressions.
 */
class DivExpr : public Expr {
public:
  // Constructor
  DivExpr() {}

  // Destructor
  virtual ~DivExpr() {}

  // Evaluation function
  virtual double eval(double x) const;
};

/**
 * @class X
 * @brief Class representing the variable x in expressions.
 */
class X : public Expr {
public:
  X() {}

  double eval(double x) const {
    return x;
  }
};

/**
 * @class Pi
 * @brief Class representing the constant pi in expressions.
 */
class Pi : public Expr {
public:
  Pi() {}

  virtual double eval(double x) const;
};

/**
 * @class LiteralNumber
 * @brief Class representing a constant number in expressions.
 */
class LiteralNumber : public Expr {
private:
  double m_value;

public:
  LiteralNumber(double value) : m_value(value) {}

  virtual double eval(double x) const;
};

/**
 * @class Sin
 * @brief Class representing the sine function in expressions.
 */
class Sin : public Expr {
private:
  Expr *m_arg;

public:
  Sin(Expr *arg) : m_arg(arg) {}

  ~Sin() {
    delete m_arg;
  }

  virtual double eval(double x) const;

  virtual void addChild(Expr* expr);
};

/**
 * @class Cos
 * @brief Class representing the cosine function in expressions.
 */
class Cos : public Expr {
private:
  Expr *m_arg;

public:
  Cos(Expr *arg) : m_arg(arg) {}

  ~Cos() {
    delete m_arg;
  }

  virtual double eval(double x) const;

  virtual void addChild(Expr* expr);
};

#endif // EXPR_H
