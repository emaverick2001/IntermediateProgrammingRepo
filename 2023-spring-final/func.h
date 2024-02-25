// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"

/**
 * @class Function
 * @brief Class representing a mathematical function with a name and an expression.
 */
class Function {
private:
  // A function has a name and an expression computing its value (given x)
  std::string m_name;
  Expr *m_expr;

  // Value semantics prohibited
  Function(const Function &);
  Function &operator=(const Function &);

public:
  /**
   * @brief Constructor for the Function class.
   * @param name The name of the function.
   * @param expr The expression representing the function.
   */
  Function(const std::string &name, Expr *expr);

  /**
   * @brief Destructor for the Function class.
   */
  ~Function();

  /**
   * @brief Getter for the name of the function.
   * @return The name of the function.
   */
  std::string get_name() const { return m_name; }

  /**
   * @brief Getter for the expression of the function.
   * @return A pointer to the expression of the function.
   */
  Expr *get_expr() const       { return m_expr; }
};

#endif // FUNC_H
