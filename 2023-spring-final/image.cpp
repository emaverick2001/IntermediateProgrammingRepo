// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include "pnglite.h"
#include "exception.h"
#include "image.h"

namespace {
// intialize pnglite
struct InitializePnglite {
  InitializePnglite() {
    ::png_init(0, 0);
  }
};

InitializePnglite init_pnglite;
// write output data
unsigned ostream_png_write_callback(void* input, size_t size, size_t numel, void* user_pointer) {
  std::ostream &out = *(reinterpret_cast<std::ostream *>(user_pointer));
  out.write(reinterpret_cast<const char *>(input), size * numel);
  if (!out.good()) {
    throw PlotException("Error writing output data");
  }
  return numel;
}

} // end anonymous namespace

Image::Image(int width, int height)
  : m_width(width)
  , m_height(height)
  , m_pixels(new Color[width * height]) {
}

Image::~Image() {
  // Deallocate memory
  delete[] m_pixels;
  
}

// Set pixel at (x, y) to color
void Image::set_pixel(int x, int y, const Color &color) {  
  m_pixels[y * m_width + x] = color;
}

// Get pixel at (x, y)
Color Image::get_pixel(int x, int y) const {
  //Check to make sure valid coordinates are provided 
  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    throw PlotException("Invalid pixel coordinates");
  }
  return m_pixels[y * m_width + x];
}

void Image::write_png(std::ostream &out)
{
  // Set up png_t object for output
  png_t png;
  int rc;

  rc = png_open_write(&png, ostream_png_write_callback, static_cast<void*>(&out));
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error opening PNG output");
  }

  // get pixel data as unsigned char *
  const unsigned char *pixels_raw_const = reinterpret_cast<const unsigned char *>(get_pixels());
  unsigned char *pixels_raw = const_cast<unsigned char *>(pixels_raw_const);

  // Write PNG data
  rc = png_set_data(&png, unsigned(m_width), unsigned(m_height), 8, PNG_TRUECOLOR,
                   pixels_raw);
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error converting writing image data as PNG");
  }
}

