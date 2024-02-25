// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#ifndef BOUNDS_H
#define BOUNDS_H

/**
 * @class Bounds
 * @brief Represents the bounds for a plot or a region in a 2D space.
 */
class Bounds {
private:
  // Defining the bounds of the plot and coordinates
  double xmin;
  double xmax;
  double ymin;
  double ymax;

public:
  /**
   * @brief Default constructor.
   */
  Bounds();

  /**
   * @brief Non-default constructor.
   * @param xmin The minimum x-coordinate value.
   * @param xmax The maximum x-coordinate value.
   * @param ymin The minimum y-coordinate value.
   * @param ymax The maximum y-coordinate value.
   */
  Bounds(double xmin, double xmax, double ymin, double ymax);

  /**
   * @brief Destructor.
   */
  ~Bounds();

  // Define getters for the x and y positions
  double get_xmin() const {return xmin;};
  double get_xmax() const {return xmax;};
  double get_ymin() const {return ymin;};
  double get_ymax() const {return ymax;};

  // Define setters for the x and y positions
  void set_xmin(double xmin);
  void set_xmax(double xmax);
  void set_ymin(double ymin);
  void set_ymax(double ymax);

  // Define getters for the width and height
  double get_width() const {return xmax - xmin;};
  double get_height() const {return ymax - ymin;};

  // Define setters for the width and height
  double set_width(double width);
  double set_height(double height);

  /**
   * @brief Determines if a point with the given x and y coordinates is within the bounds.
   * @param x The x-coordinate of the point.
   * @param y The y-coordinate of the point.
   * @return True if the point is within the bounds, false otherwise.
   */
  bool contains(double x, double y) const {
    return (x >= xmin && x <= xmax && y >= ymin && y <= ymax);
  }

};

#endif // BOUNDS_H
