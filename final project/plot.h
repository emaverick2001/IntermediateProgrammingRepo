#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "color.h"
#include "image.h"
#include "func.h"
#include "fill.h"

class Plot {
private:
  // TODO: add fields to represent plot bounds, functions, fills, etc.
  Bounds m_bound;
  std::map<std::string,Function*> functions;
  std::vector<Fill*> m_fill; //vector of string for key

  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &); //asignment operator

public:
  Plot();
  ~Plot();

  // TODO: add member functions to set and modify plot data

  const std::map<std::string,Function*>& getfunctionsmap() const {
    return functions;
  }

  // getfill memeber
  const std::vector<Fill*>& getfills() const{
    return m_fill;
  }

  // GETTERS!!!!!!!!!
  /*
  * Get width and height of plot
  * @return width and height of plot
  */
  int get_width() const;

  /*
  * Get height of plot
  * @return height of plot
  */
  int get_height() const;

  /*
  * Get function by name
  * @param funcname name of function
  * @return pointer to function
  */
  Function* getfunction (std::string funcname) const { return functions.at(funcname); }

  /*
  * Get bounds
  * @return bounds of plot
  */
  Bounds getBounds() const { return m_bound; }
  

  // SETTERS!!!!!!!!!
  
  /*
  * Set bounds
  * @param bound pointer to bounds of plot
  */
  void setbounds(Bounds bound) { m_bound = bound; }
  
  /*
  * Add function to plot
  * @param function pointer to function
  */
  void add_function(Function* function) { functions[function->get_name()] = function; }

  /*
  * Set color of function
  * @param fname name of function
  * @param rval red value
  * @param gval green value
  * @param bval blue value
  */
  void setfColor(std::string fname,int rval, int gval, int bval) {functions[fname]->setColor(rval,gval,bval);}
  
  /*
  * Set fill
  * @param fname name of function
  * @param fname2 name of function
  * @param opacity opacity of fill
  * @param rval red value
  * @param gval green value
  * @param bval blue value
  * @param type type of fill
  */
  void setFill(std::string fname,std::string fname2,double opacity,int rval,int gval,int bval,std::string type){
    Color col;
    col.setRval((unsigned int)rval);
    col.setGval((unsigned int)gval);
    col.setBval((unsigned int)bval);
    m_fill.push_back(new Fill(fname,fname2,opacity,col,type));
  }

  bool has_function(std::string fname){
        bool hasfunc = false;
        std::map<std::string, Function*> temp = this->getfunctionsmap();
        for (auto it : temp){
            if(it.first == fname){
                hasfunc = true;
            }
        }
        return hasfunc;
    }

  /**
  * Check if a function name exists
  * @param name the name of the function to check
  * @return true if the function exists, false otherwise
  */
  bool check_function_name_exists(std::string name) const;
};

#endif // PLOT_H
