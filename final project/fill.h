#ifndef FILL_H
#define FILL_H

#include <string>
#include "color.h"
#include "image.h"
#include "func.h"
#include <map>


class Fill {
private:

  std::string m_funcname;
  std::string m_funcname2;
  double m_opacity;        // opacity value between 0 and 1
  Color m_color;    // color of the fill
  std::string m_type;


public:
  // TODO: add appropriate constructors


  // constructors
  Fill() : m_funcname(""), m_funcname2(""), m_opacity(0.0), m_color(), m_type("") {}
  Fill(const std::string funcname, const std::string funcname2,const double opacity, const Color& color, const std::string type);
  
  ~Fill();

  // copy constructor
  Fill(const Fill& other);

  //assignment operator
  Fill& operator=(const Fill& other);

  // TODO: add appropriate member functions

  Color get_color() const {return m_color;}
  double get_opacity() const {return m_opacity;}
  

  void set_color(Color& color);
  void set_opacity(double& opacity);

  /**
  * Gets the first function of the fill
  * @return the first function of the fill
  */
  std::string get_function1() const;

  /**
  * Gets the second function of the fill
  * @return the second function of the fill
  */
  std::string get_function2() const;


  /**
  * Gets the type of fill
  * @return the type of fill
  */
  std::string get_fill_type() const;

};

#endif // FILL_H
