#include "maze.h"
#include "print_functions.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * \file hw3.c
 * \brief The main driver function of HW 3
 *
 * \details This source file implements the main function for HW 3. It checks
 * the input command line arguments and calls the corresponding modules.
 */

int main(int argc, char *argv[]) {
  int return_code = 0;

  // check input arguments
  // solve maze: ./hw3 <maze_file>
  // gen maze: ./hw3 <maze_file> <width> <height> [threshold = 0.5] [seed = 0]

  if (argc < 2 || argc == 3 || argc > 6) {
    return_code = 2; // invalid input arguments
  } else {
    char maze[200][200];
    int maze_width = 0;
    int maze_height = 0;
    char *filename = argv[1];
    if (argc == 2) { // solve maze
      // read file
      return_code = readMaze(
          filename, maze, &maze_width,
          &maze_height); // TODO: replace with call to your readMaze function
      if (!return_code) {
        // print maze
        printMaze(maze, maze_width, maze_height);
        // solve maze
        char sol[200][200];
        return_code = solveMaze(maze, maze_width, maze_height, sol);
        if (!return_code) {
          // print solution
          printSolution(maze, maze_width, maze_height, sol);
        }
      }
    } else { // gen maze
      // parse input arguments
      int seed = 0;
      double threshold = 0.5;
      // TODO: add your argument parsing code and input validation code here
      char *filename_output = argv[1];
      maze_width = atoi(argv[2]);
      maze_height = atoi(argv[3]);
      if (maze_height < 0 || maze_width < 0) {
        return -3;
      }

      if (argc == 5) {
        threshold = atof(argv[4]);
      }
      if (argc == 6) {
        threshold = atof(argv[4]);
        seed = atoi(argv[5]);
      }
      

      // remember to set the correct return_code

      if (!return_code) {
        // gen maze
        genMaze(maze, maze_width, maze_height, threshold, seed);
        // print maze
        printMaze(maze, maze_width, maze_height);
        // write maze
        return_code = writeMaze(
            filename_output, maze, &maze_width,
            &maze_height); // TODO: replace with call to your writeMaze function
      }
    }
  }

  if (return_code)
    printError(return_code, argv);

  return return_code;
}
