#include "print_functions.h"
#include <stdio.h>

/**
 * \file print_functions.c
 * \brief Provides print-related functionalities
 *
 * \details This source file implements all print-related functionalities for printing the maze, solution, and errors
 */

// The function to print the maze
void printMaze(char maze[][200], const int maze_width, const int maze_height)
{
  // TODO: implement this function
  printf("Maze: %d, %d\n", maze_width, maze_height);

  // print maze
  for (int i = 0; i < maze_height; i++)
  {
    printf("%s\n", maze[i]);
  }
}

// The function to print the maze's solution
void printSolution(char maze[][200], const int maze_width, const int maze_height, char sol[][200])
{
  // TODO: implement this function
  if(!maze[maze_height][maze_width]){
  printf("Solution path (*):\n");
  for (int row = 0; row < maze_height; row++)
  {
    for (int col = 0; col < maze_width; col++)
    {
      printf("%c", sol[row][col]);
    }
    printf("\n");
  }
}
}

// The function to print the error message
void printError(const int return_code, char *argv[])
{
  // TODO: implement this function
  char *filename = argv[1];

  switch (return_code)
  {
  case 1:

    printf("Info: No solution found for the input maze\n");

    break;

  case 2:

    printf("Generate maze usage: ./hw3 <maze file> <width> <height> [threshold = 0.5] [seed = 0]\n");
    printf("Solve maze usage: ./hw3 <maze file>\n");

    break;

  default:

    fprintf(stderr, "Other program error: %s\n", filename);
  }
}
