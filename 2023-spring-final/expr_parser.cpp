// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include <iostream>
#include <cctype> // added for std::isdigit()
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

using std::string;
using std::deque;

// Default constructor for ExprParser
ExprParser::ExprParser() {
}

// Destructor for ExprParser
ExprParser::~ExprParser() {
}

// Helper function used to determine if a string is numeric, true if numeric else false
// This function helped solve an issue with the program reading "-" as a subtraction rather than negative sign 
bool ExprParser::is_numeric(const string& str) {
  for (char c : str) {
    if (!isdigit(c) && c != '.') {
      return false;
    }
  }
  return !str.empty();
}

// Helper function to parse expression from deque of tokens
// Throws PlotException if any error in the input tokens
Expr* ExprParser::parsePfxExpr(deque<string>& tokens) {
  // Check if there is any tokens left
  if (tokens.empty()) {
    throw PlotException("Empty");
  }

  // Get the current token and remove from the tokens deque 
  string n = tokens.front();
  tokens.pop_front();

  // Check if the current token is x, pi, or natural number 
  if (n == "x" || n == "pi" || this->is_numeric(n)) {
    // If n is numeric, create LiteralNumber node with value 
    if (this->is_numeric(n)) {
      double value = std::stod(n);
      return new LiteralNumber(value);
    }
    // Else create a pi node 
    else if (n == "pi") {
      return new Pi();
    }
    // Else create a X node 
    else {
      return new X();
    }
  }
  // If n is opening parenthesis, parse the function call
  else if (n == "(") {
    if (tokens.empty()) {
      throw PlotException("Empty");
    }

    n = tokens.front();
    tokens.pop_front();

    // Check that the function name is valid 
    if (n != "sin" && n != "cos" && n != "+" && n != "-" && n != "*" && n != "/") {
      throw PlotException("Invalid operation");
    }

    // Create appropriate function node based on the name
    Expr* result = nullptr;
    // For sin, create sin node and parse 
    if (n == "sin") {
      if (tokens.empty()) {
        throw PlotException("Missing argument for sin");
      }
      else if (!tokens.empty() && tokens.front() == ")") {
        throw PlotException("Missing argument for sin");
      }

      Expr* arg = parsePfxExpr(tokens);
      result = new Sin(arg);
    }
    // Else for cos, create cos node and parse 
    else if (n == "cos") {
      if (tokens.empty()) {
        throw PlotException("Missing argument for cos");
      }
      else if (!tokens.empty() && tokens.front() == ")") {
        throw PlotException("Missing argument for cos");
      }
      Expr* arg = parsePfxExpr(tokens);
      result = new Cos(arg);
    }
    // For other operators create the corresponding node 
    else if (n == "+") {
      result = new AddExpr();
    }
    else if (n == "-") {
      result = new SubExpr();
    }
    else if (n == "*") {
      result = new MultExpr();
    }
    else if (n == "/") {
      result = new DivExpr();
    }

    // Parse function arguments and add as child 
    while (!tokens.empty() && tokens.front() != ")") {
      Expr* arg = parsePfxExpr(tokens);
      result->addChild(arg);
    }

    // Error handling for number of operands required by each operator
    if ((n == "+" || n == "-" || n == "*" || n == "/") && result->numChildren() == 0) {
      throw PlotException("Operators require at least one operand");
    } else if ((n == "-" || n == "/") && result->numChildren() != 2) {
      throw PlotException("Subtraction and division require exactly two operands");
    }

    // Check for any remaining tokens, or if right parenthesis is missing 
    if (tokens.empty()) {
      throw PlotException("Missing right parenthesis");
    }

    // Remove right parenthesis from deque and return node 
    tokens.pop_front();
    return result;
  }
  // If not x, pi, or literal number 
  else {
    throw PlotException("Unexpected token");
  }
}

// Parses expression from provided input stream
// Returns pointer to the Expr object representing the parsed expression 
Expr* ExprParser::parse(std::istream& in) {
  // Creates a deque to store input tokens and declares string to hold each token
  deque<string> tokens;
  string token;

  // Read from the token and add to the tokens deque 
  while (in >> token) {
    tokens.push_back(token);
  }

  // Creates a copy of the deque to be passed to parsePfxExpr function 
  deque<string> tokenDeque(tokens.begin(), tokens.end());
  // Calls helper function to parse expression and returns the parsed expression 
  Expr* parsedExpr = parsePfxExpr(tokenDeque);
  if (!(tokenDeque.empty())) {
    throw PlotException("Invalid arguments to expression");
  }

  return parsedExpr;
}
