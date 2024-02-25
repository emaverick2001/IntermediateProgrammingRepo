#include <cassert>
#include "bounds.h"
#include "plot.h"

using std::vector;
using std::map;
using std::string;

Plot::Plot() {
  functions = map<string,Function*>();
  m_bound = Bounds();
  m_fill = vector<Fill*>();

} //calling object member fields default constructor for clarity

Plot::~Plot()
{
  // TODO: delete dynamically-allocated objects,

  for (map<string,Function*>::iterator it = functions.begin(); it != functions.end(); ++it)
  {
    delete it->second;
  }

  for (vector<Fill*>::iterator it = m_fill.begin(); it != m_fill.end(); ++it)
  {
    delete *it;
  }

}

bool Plot::check_function_name_exists(std::string name) const {
    return functions.find(name) != functions.end();
}

int Plot::get_width() const{
  return m_bound.get_width();
}

int Plot::get_height() const{
  return m_bound.get_height();
}
