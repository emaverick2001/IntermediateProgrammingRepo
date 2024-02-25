// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  // Define private fields 
  int m_width, m_height;
  Color *m_pixels;

  // value semantics are prohibited
  Image(const Image &);
  Image &operator=(const Image &);

public:
  // Default constructor and destructor 
  Image(int width, int height);
  ~Image();

  // Define getters and setters for width, height, and pixels
  int get_width() const { return m_width; }
  int get_height() const { return m_height; }

  void set_pixel(int x, int y, const Color &color);
  Color get_pixel(int x, int y) const;
  const Color* get_pixels() const {return m_pixels;}

  void write_png(std::ostream &out);
};

#endif // IMAGE_H
