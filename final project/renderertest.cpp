#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "renderer.h"


int main(){
    return 0;

//     int main(int argc, char **argv){
//   std::cout << "hi" << std::endl;

//   std::ofstream out(argv[1]);
//   if (!out.is_open()) {
//     std::cerr << "Error: couldn't open output file " << argv[1] << "\n";
//     return 1;
//   }

//   Plot plot;

//   // render the plot to an Image
//   Renderer renderer(plot);
//   std::unique_ptr<Image> img(renderer.render());

//   // write the Image as a PNG file
//   img->write_png(out);
//   std::cout << "Wrote plot image successfully!\n";

//   return 0;
// }
}