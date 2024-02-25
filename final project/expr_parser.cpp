// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#include "expr_parser.h"
#include "exception.h"
#include <string>
#include <cctype>
#include <sstream>

ExprParser::ExprParser(){ 
}

ExprParser::~ExprParser() {
}

// void ExprParser::clear_mem() {
//   clear_expr(parsedExpr); 
//   parsedExpr = nullptr; 
// }

// void ExprParser::clear_expr(Expr* expr) {
//     if (expr) {
//         for (size_t i = 0; i < expr->numChildren(); ++i) {
//             clear_expr(expr->getChild(i));
//         }
//         delete expr;
//     }
// }

// helper func to check if string is numeric and works for floats and negative vals
bool ExprParser::is_numeric(const std::string& str) {
    if (str.empty())
        return false;

    bool hasDecimalPoint = false;
    bool hasDigits = false;

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        if (i == 0 && (c == '-' || isdigit(c))) {
            // First character can be a minus sign or a digit (for negative numbers)
            if (c == '-')
                continue;
            hasDigits = true;
        } else if (isdigit(c)) {
            // Subsequent characters must be digits
            hasDigits = true;
        } else if (c == '.' && !hasDecimalPoint) {
            // Allow one decimal point in the string
            hasDecimalPoint = true;
        } else {
            return false;
        }
    }

    // Ensure the string contains at least one digit
    return hasDigits;
}


Expr* ExprParser::parsePfxExpr(std::deque<std::string>& tokens) {
    
    if (tokens.empty()) {
    throw PlotException("Empty expression");
    }

    std::string n = tokens.front();
    tokens.pop_front();

    // Check if the current token is x, pi, or natural number 
    if (n == "x" || n == "pi" || is_numeric(n)) {

      //create Literal value
      if (is_numeric(n)) {
        double value = std::stod(n);
        return new Literal(value);
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
    //check to see if begin parentheses
    else if (n == "(") {
      if (tokens.empty()) {
      throw PlotException("Empty");
      } 
      
      n = tokens.front();
      tokens.pop_front();

      //checking to see if there are no function names @ this point
      if (n != "sin" && n != "cos" && n != "+" && n != "-" && n != "*" && n != "/") {
          throw PlotException("Invalid function name"); // Invalid function name
      }

      // Create appropriate function node based on the name
      Expr* result = nullptr;

        // create a Sin node 
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

      // create a Cos node 
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

      // create a addition node 
      else if (n == "+") {
        result = new Add();
      }

      // create a subtract node 
      else if (n == "-") {
        result = new Subtract();
      }

      // create a mult node 
      else if (n == "*") {
        result = new Multiply();
      }
      // create a mult node 
      else if (n == "/") {
        result = new Divide();
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

        tokens.pop_front(); // Remove the closing parenthesis )

        return result;
        
    } else {
        throw PlotException("Unexpected token"); // Unexpected token
    }
}


Expr* ExprParser::parse(std::stringstream& in) {
  // Creates a deque to store each token
  std::deque<std::string> tokens;
  std::string token;

  // Read from token and add to deque 
  while (in >> token) {
    tokens.push_back(token);
  }

  // Calls helper function to parse expression and returns the parsed expression 
  Expr* parsedExpr = parsePfxExpr(tokens);
  if (!(tokens.empty())) {
    throw PlotException("Invalid arguments to expression");
  }
  return parsedExpr;
}