#include "pnglite.h"
#include "exception.h"
#include "image.h"

namespace {

struct InitializePnglite {
  InitializePnglite() {
    ::png_init(0, 0);
  }
};

InitializePnglite init_pnglite; 

unsigned ostream_png_write_callback(void* input, size_t size, size_t numel, void* user_pointer) {
  std::ostream &out = *(reinterpret_cast<std::ostream *>(user_pointer));
  out.write(reinterpret_cast<const char *>(input), size * numel);
  if (!out.good()) {
    throw PlotException("Error: writing output data");
  }
  return numel;
}

} // end anonymous namespace

Image::Image(int width, int height)
  : m_width(width)
  , m_height(height)
  , m_pixels(new Color[width * height]) {
  // TODO: initialize pixel data
  for (int i = 0; i < m_height; i++){
    for (int j = 0; j < m_width; j++){
      m_pixels[i*m_width+j].r = 0;
      m_pixels[i*m_width+j].g = 0;
      m_pixels[i*m_width+j].b = 0;
    }
  }
}

Image::~Image() {
  // TODO: deallocate memory
    delete[] m_pixels; //check
}

// TODO: implement member functions

void Image::set_pixel(int x, int y, const Color &color){
  //Check valid coordinates are provided 
  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    throw PlotException("Invalid pixel coordinates");
  }
  m_pixels[y * m_width + x] = color;
}

Color Image::get_pixel(int x, int y) const {
  //Check valid coordinates are provided 
  if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
    throw PlotException("Invalid pixel coordinates");
  }
  return m_pixels[y * m_width + x]; //pixels are stored in 1d array
}

void Image::write_png(std::ostream &out)
{
  // Set up png_t object for output
  png_t png;
  int rc;

  rc = png_open_write(&png, ostream_png_write_callback, static_cast<void*>(&out));
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error: opening PNG output");
  }

  // get pixel data as unsigned char *
  const unsigned char *pixels_raw_const = reinterpret_cast<const unsigned char *>(get_pixels());
  unsigned char *pixels_raw = const_cast<unsigned char *>(pixels_raw_const);

  // Write PNG data
  rc = png_set_data(&png, unsigned(m_width), unsigned(m_height), 8, PNG_TRUECOLOR,
                   pixels_raw);
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error: converting writing image data as PNG");
  }
}
