// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef READER_H
#define READER_H

#include "plot.h"
#include <istream>

/**
 * @class Reader
 * @brief Class responsible for reading plot descriptions and validating function names.
 */
class Reader {
private:
  // Copy constructor and assignment operator are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);

public:
  /**
   * @brief Default constructor for the Reader class.
   */
  Reader();

  /**
   * @brief Destructor for the Reader class.
   */
  ~Reader();

  /**
   * @brief Reads plot description from the given input stream and adds it to the Plot object.
   * @param in Input stream containing plot description.
   * @param plot Plot object to which the description will be added.
   * @throws PlotException If any errors are found in the plot description.
   */
  void read_input(std::istream &in, Plot &plot);

  /**
   * @brief Validates the provided function names against the available functions in the plot.
   * @param plot Plot object containing the available functions.
   * @param fn_name1 First function name to validate.
   * @param fn_name2 Second function name to validate.
   */
  void validate_function_names(const Plot &plot, const std::string &fn_name1, const std::string &fn_name2);
};

#endif // READER_H
