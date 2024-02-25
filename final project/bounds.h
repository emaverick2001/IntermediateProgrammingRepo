#ifndef BOUNDS_H
#define BOUNDS_H

class Bounds {
   private:
    // TODO: add fields
    float m_xmin;
    float m_xmax;
    float m_ymin;
    float m_ymax;
    float m_wdim;  // width dimension
    float m_ldim;  // length dimension

   public:
    // TODO: add member functions
    Bounds();
    Bounds(float xmin, float xmax, float ymin, float ymax, int wdim, int ldim);
    ~Bounds();

    // copy constructor
    Bounds(const Bounds& other);

    // assignment operator
    Bounds& operator=(const Bounds& other);

    // other functions
    // check if bounds are valid
    bool isValidBound();

    // get width
    float get_width() const;

    // get height
    float get_height() const;

    // get each min and max value
    float get_xmin() const;
    float get_xmax() const;
    float get_ymin() const;
    float get_ymax() const;
};
#endif  // BOUNDS_H
