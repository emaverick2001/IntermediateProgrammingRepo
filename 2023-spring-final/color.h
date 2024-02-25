// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cassert>

/**
 * @struct Color
 * @brief Represents a color using RGB (red, green, blue) values.
 */
struct Color {
  uint8_t r, g, b;

  /**
   * @brief Constructor for the Color struct.
   * Initializes color components with provided values, or zero if not provided.
   * @param r The red component of the color [0, 255].
   * @param g The green component of the color [0, 255].
   * @param b The blue component of the color [0, 255].
   */
  Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) { }
};

#endif // COLOR_H
