// Maverick Espinosa mespin11
// Ria Dani rdani1
// Katharine Forbes kforbes6
#include "reader.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "bounds.h"
#include "exception.h"
#include "expr_parser.h"
#include "fill.h"
#include "plot.h"

using std::string;
using std::stringstream;

Reader::Reader() {
}

Reader::~Reader() {}

void Reader::read_input(std::istream &in, Plot &plot) {
    stringstream ss;
    stringstream tkn;

    // TODO: A plot input file must specify exactly one Plot directive.
    // read plot input from in, add information to plot
    while (getline(in, inputLine)) {
        ss.clear();
        ss.str(inputLine);
        if (!ss){
            throw PlotException("Error: no line was read");
        }

        ss >> directive_name;

        if (directive_name == "Plot") {

            if (!(ss >> xmin >> ymin >> xmax >> ymax >> wdim >> ldim)) {
                throw PlotException("Error: Failed to read values");
            }

            Bounds bound(xmin, xmax, ymin, ymax, wdim, ldim);

            if (!bound.isValidBound()) {
                throw PlotException("Error: Invalid bounds");
            }
            if (ss >> inputLine) {
                throw PlotException("Error: Too many arguments");
            }
            if (wdim <= 0 || ldim <= 0) {
                throw PlotException("Error: Invalid image size");
            }
            plot.setbounds(bound);

        } else if (directive_name == "Function") {
            if (!(ss >> fname)) {
                throw PlotException("Error: Cannot read function name");
            }

            // Check if function name already exists 
            if (plot.has_function(fname)) {
                throw PlotException("Function already exists");
            }

            // get expression string and store only in ss
            getline(ss, expression);
            if (!ss){
                throw PlotException("Error: no expression found");
            }
            expression.erase(0, expression.find_first_not_of(" \t"));
            ss.clear();
            ss.str("");
            std::stringstream ss(expression);
            ExprParser parser;
            Function *func = new Function(fname, parser.parse(ss));
            plot.add_function(func);

        } else if (directive_name == "Color") {
            ss >> fname;
            ss >> rval;
            ss >> gval;
            ss >> bval;
            if (rval > 255 || gval > 255 || bval > 255 || rval < 0 || gval < 0 || bval < 0) {
                throw PlotException("Error: Invalid color");
            }
            plot.setfColor(fname, rval, gval, bval);
        } else if (directive_name == "FillAbove" || directive_name == "FillBelow") {
            ss >> fname;
            ss >> opacity;
            ss >> rval;
            ss >> gval;
            ss >> bval;
            if (rval > 255 || gval > 255 || bval > 255 || rval < 0 || gval < 0 || bval < 0) {
                throw PlotException("Error: Invalid color");
            }
            if (opacity < 0 || opacity > 1) {
                throw PlotException("Error: Invalid opacity");
            }

            if (directive_name == "FillAbove") {
                plot.setFill(fname, "", opacity, rval, gval, bval, directive_name);
            } else if (directive_name == "FillBelow") {
                plot.setFill(fname, "", opacity, rval, gval, bval, directive_name);
            }
        } else if (directive_name == "FillBetween") {
            ss >> fname;
            ss >> fname2;
            ss >> opacity;
            ss >> rval;
            ss >> gval;
            ss >> bval;

            if (rval > 255 || gval > 255 || bval > 255 || rval < 0 || gval < 0 || bval < 0) {
                throw PlotException("Error: Invalid color");
            }
            if (opacity < 0 || opacity > 1) {
                throw PlotException("Error: Invalid opacity");
            }

            plot.setFill(fname, fname2, opacity, rval, gval, bval, directive_name);
        } else {
            // Invalid command case
            throw PlotException("Error: Invalid directive");
        }
    }
}
