#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

class Renderer {
private:
  // it's convenient to have these as fields, to avoid the need
  // to pass them explicitly to helper functions
  const Plot &m_plot;
  Image *m_img;

  // value semantics prohibited
  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);
  

public:
  Renderer(const Plot &plot);
  ~Renderer();

  Image *render();

private:
  // TODO: add private helper functions

  bool isValidFill(const Fill* fill, double x, double y,std::string name1, std::string name2);
  int find_pixel_row(int j, const Expr *f, double x_min, double x_max, double y_min, double y_max, int width, int height);
  void draw_pixel(int x, int y, Color &func_color);
};

#endif // RENDERER_H
