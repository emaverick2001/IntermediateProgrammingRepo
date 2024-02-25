// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#ifndef READER_H
#define READER_H

#include <istream>

#include "bounds.h"
#include "color.h"
#include "expr.h"
#include "expr_parser.h"
#include "fill.h"
#include "func.h"
#include "image.h"
#include "plot.h"
#include "renderer.h"

using std::string;
using std::stringstream;

class Reader {
   private:
    // value semantics are prohibited
    Reader(const Reader &);
    Reader &operator=(const Reader &);
    string inputLine = "";
    string directive_name = "";
    float xmin = 0.0;
    float xmax = 0.0;
    float ymin = 0.0;
    float ymax = 0.0;
    int wdim = 0;
    int ldim = 0;
    string fname = "";
    string expression = "";
    string fname2 = "";
    int rval = 0;
    int gval = 0;
    int bval = 0;
    float opacity = 0.0;

   public:
    Reader();
    ~Reader();

    // read plot description from given istream;
    // throw a PlotException if any errors are found
    void read_input(std::istream &in, Plot &plot);
};

#endif  // READER_H