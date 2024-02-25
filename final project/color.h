#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cassert>

struct Color {
  uint8_t r, g, b;

  // member functions for doing operations on Color values

  Color() : r(255), g(255), b(255) {}

  //setters
  void setRval(uint8_t rval) {r = rval;}
  void setGval(uint8_t gval) {g = gval;}
  void setBval(uint8_t bval) {b = bval;}
  // could be helpful
};

#endif // COLOR_H
