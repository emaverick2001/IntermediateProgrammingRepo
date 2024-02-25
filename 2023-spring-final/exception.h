// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class PlotException : public std::runtime_error {
public:
  // Constructor for PlotException
  PlotException(const std::string &msg);
  // Copy Constructor for PlotException
  PlotException(const PlotException &other);
  // Destructor for PlotException 
  ~PlotException();
};

#endif // EXCEPTION_H
