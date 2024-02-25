// Nikhil Choudhary - nchoudh5
// Sun Moon - gmoon3 
// Edgar Robitaille - erobita1
#include <cassert>
#include "fill.h"

// Non-default Constructor for Fill Above and Fill Below
Fill::Fill(FillType fill_type, const std::string& fn_name1, double opacity, const Color& color)
    : fill_type_(fill_type), fn_name1_(fn_name1), opacity_(opacity), color_(color) {
}

// Separate Constructor for FillBetween due to a different formatting 
Fill::Fill(FillType fill_type, const std::string& fn_name1, const std::string& fn_name2, double opacity, const Color& color)
    : fill_type_(fill_type), fn_name1_(fn_name1), fn_name2_(fn_name2), opacity_(opacity), color_(color) {
}
// Destructor 
Fill::~Fill() {
}
