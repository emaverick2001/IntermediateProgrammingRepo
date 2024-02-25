#include "bounds.h"

// TODO: implement member functions

Bounds::Bounds() : m_xmin(0.0), m_xmax(0.0), m_ymin(0.0), m_ymax(0.0), m_wdim(0), m_ldim(0) {}
Bounds::Bounds(float xmin, float xmax, float ymin, float ymax, int wdim, int ldim) {
    this->m_xmin = xmin;
    this->m_ymin = ymin;
    this->m_xmax = xmax;
    this->m_ymax = ymax;
    this->m_wdim = wdim;
    this->m_ldim = ldim;
}
Bounds::~Bounds() {}

bool Bounds::isValidBound() {
    if (m_wdim <= 0 || m_ldim <= 0 || m_xmin >= m_xmax || m_ymin >= m_ymax) {
        return false;
    }
    return true;
}

float Bounds::get_width() const {
    return m_wdim;
}

float Bounds::get_height() const {
    return m_ldim;
}
float Bounds::get_xmin() const {
    return m_xmin;
}
float Bounds::get_xmax() const {
    return m_xmax;
}
float Bounds::get_ymin() const {
    return m_ymin;
}
float Bounds::get_ymax() const {
    return m_ymax;
}

// copy constructor
Bounds::Bounds(const Bounds& other)
    : m_xmin(other.m_xmin),
      m_xmax(other.m_xmax),
      m_ymin(other.m_ymin),
      m_ymax(other.m_ymax),
      m_wdim(other.m_wdim),
      m_ldim(other.m_ldim) {
    // If any of the members are pointers or dynamically allocated resources,
    // perform deep copy in the copy constructor.
}

// assignment operator
Bounds& Bounds::operator=(const Bounds& other) {
    if (this == &other) {
        // Self-assignment check; do nothing if assigning to itself
        return *this;
    }

    // Copy the values from the other object to this object
    m_xmin = other.m_xmin;
    m_xmax = other.m_xmax;
    m_ymin = other.m_ymin;
    m_ymax = other.m_ymax;
    m_wdim = other.m_wdim;
    m_ldim = other.m_ldim;

    // Return a reference to this object
    return *this;
}