// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

/**
 * @class Renderer
 * @brief Class responsible for rendering the plot and its components, such as fills and functions.
 */
class Renderer {
private:
  // Fields to store a reference to the Plot object and a pointer to the Image object
  const Plot &m_plot;
  Image *m_img;

  // Prohibit value semantics
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

  // Helper functions declarations

  // Draws a pixel of given color at the specified location
  void draw_pixel(int x, int y, Color &func_color); 
  // Renders fill areas on the plot
  void renderFills();
  // Renders functions on the plot 
  void renderFunctions(); 
  // Blends two colors based on alpha value
  Color color_blend(const Color& orig, const Color& fill, double alpha); 
  // Converts pixel indices to corresponding x, y coordinates
  std::pair<double, double> pixel_to_XY(int i, int j, double x_min, double x_max, double y_min, double y_max, int width, int height); 
  // Finds the pixel row for a given function and column index
  int find_pixel_row(int j, const Expr *f, double x_min, double x_max, double y_min, double y_max, int width, int height); 
  // Returns a pointer to the function with the given name, or nullptr if not found
  const Function* get_func_name(const std::string& name); 
  // Checks if a given fill is valid for a point (x, y)
  bool is_valid_fill(const Fill* fill, double x, double y); 

public:
  /**
   * @brief Non-default constructor for the Renderer class.
   * @param plot Reference to the Plot object to be rendered.
   */
  Renderer(const Plot &plot);

  /**
   * @brief Destructor for the Renderer class.
   */
  ~Renderer();

  /**
   * @brief Renders the plot and its components to an Image object.
   * @return Pointer to the rendered Image object.
   */
  Image *render();

};

#endif // RENDERER_H
