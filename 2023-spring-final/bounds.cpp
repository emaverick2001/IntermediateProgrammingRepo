// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include "bounds.h"

// Default constructor setting all coordinates to 0
Bounds::Bounds () { xmin = 0; xmax = 0; ymin = 0; ymax = 0; }; 

// Non-default constructor setting all coordinates to the given values
Bounds::Bounds(double xmin, double xmax, double ymin, double ymax) {
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
}

// Destructor 
Bounds::~Bounds () {};

// Setters for the private variables positions
void Bounds::set_xmin (double xmin) {this->xmin = xmin;};
void Bounds::set_xmax (double xmax) {this->xmax = xmax;};
void Bounds::set_ymin (double ymin) {this->ymin = ymin;};
void Bounds::set_ymax (double ymax) {this->ymax = ymax;};
