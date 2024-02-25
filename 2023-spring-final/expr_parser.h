// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef FN_PARSER_H
#define FN_PARSER_H

#include <iostream>
#include <deque>
#include "expr.h"

/**
 * @class ExprParser
 * @brief Expression parser that reads and parses mathematical expressions from an input stream.
 */
class ExprParser {
private:
  // Prohibit value semantics by declaring copy constructor and assignment operator as private
  ExprParser(const ExprParser &);
  ExprParser &operator=(const ExprParser &);

  // Helper function that parses expressions in prefix notation from a deque of tokens
  Expr* parsePfxExpr(std::deque<std::string>& tokens);

  // Helper function to check if a string is numeric
  bool is_numeric(const std::string& str);

public:
  // Default constructor for ExprParser
  ExprParser();

  // Destructor for ExprParser
  ~ExprParser();

  /**
   * @brief Parses a mathematical expression from the given input stream.
   * @param in The input stream from which the expression is read.
   * @return A pointer to the root of the parsed expression tree.
   */
  Expr *parse(std::istream &in);
};

#endif // FN_PARSER_H
