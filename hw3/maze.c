#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * \file maze.c
 * \brief Provides maze-related functionalities
 *
 * \details This source file implements all maze-related functionalities for reading/writing/solving/generating the maze and releasing related memories.
 */

/* The function to read the maze from a file given the filename, maze
   array, maze width and maze height: open file, read sizes, read maze, close file
*/
// TODO: write the entirety of this readMaze function
int readMaze(char filename[], char maze[][200], int *width, int *height)
{
  FILE *input = fopen(filename, "r");

  if (input == NULL)
  {
    return -1;
  }

  int line = 0;
  char inputs[200];
  fgets(inputs, 200, input);
  int parse = sscanf(inputs, "%d %d", width, height);

  if (parse != 2)
  {
    fclose(input);
    return -2;
  }
  // printf("%d %d",*width, *height);
  while ((fgets(maze[line], 200, input)) != NULL)
  {
    // printf("%s",maze[line]);
    for (int x = 0; x <= 200; x++)
    {
      if (maze[line][x] == '\n')
      {
        maze[line][x] = '\0';
        break;
      }
    }
    line++;
  }

  // if wrong input is given for width/height
  if (parse == -1)
  {
    return -1;
  }
  // printf("%d",parse);
  // printf("%d %d\n",*width, *height);
  fclose(input);
  return 0;
}

/* The function to write the maze to a file given the filename, maze
   array, maze width and maze height: open file, write maze, close file
*/
// TODO: write the entirety of this writeMaze function
int writeMaze(char filename[], char maze[][200], int *width, int *height)
{

  FILE *output = fopen(filename, "w");

  if (output == NULL)
  {
    return -4;
  }
  // write inputs
  fprintf(output, "%d %d\n", *width, *height);
  if (ferror(output))
  {
    fclose(output);
    return -5;
  }
  int line = 0;
  // write maze
  while (line < *height)
  {
    // printf("%s",maze[line]);
    fprintf(output, "%s\n", maze[line]);
    line++;
  }

  fclose(output);
  return 0;
}

// The function to solve a solution path for the maze
int solveMaze(char maze[][200], const int maze_width, const int maze_height, char sol[][200])
{
  // TODO: implement this function
  int startRow = -1;
  int startCol = -1;
  for (int row = 0; row < maze_height; row++)
  {
    for (int col = 0; col < maze_width; col++)
    {
      if (maze[row][col] == '@')
      {
        startRow = row;
        startCol = col;
        break;
      }
    }
    if (startRow != -1 && startCol != -1)
    {
      break;
    }
  }

  // there are no start positions
  if (startRow == -1)
  {
    return 1;
  }
  // For each position in the solution maze(sol) mark them all as unvisited
  for (int col = 0; col < maze_width; col++)
  {
    for (int row = 0; row < maze_height; row++)
    {
      sol[row][col] = maze[row][col];
    }
  }
  int found = solvePath(maze, maze_width, maze_height, startRow, startCol, sol); // TODO: replace this stub
  // Restore start position
  if (found)
  {
    sol[startRow][startCol] = '@';
  }
  // Flip the return code
  return !found;
}

// The function to solve a solution path recursively
int solvePath(char maze[][200], const int maze_width, const int maze_height, const int row, const int col, char sol[][200])
{
  // TODO: implement this function
  static int counter;

  // Check of the current position is the goal
  if (maze[row][col] == '<')
  {
    return 1;
  }
  counter++;
  if(counter > 2000) return 0;
  
  // Check if the current position is valid
  if (row >= 0 && col >= 0 && row < maze_height && col < maze_width && maze[row][col] != '#' && sol[row][col] != '*')
  {
    // Mark the current position as visited
    sol[row][col] = '*';
    // Recursively explore adjacent positions (left, right, up, down)
    if (solvePath(maze, maze_width, maze_height, row, col - 1, sol) || // Left
        solvePath(maze, maze_width, maze_height, row, col + 1, sol) || // Right
        solvePath(maze, maze_width, maze_height, row - 1, col, sol) || // Up
        solvePath(maze, maze_width, maze_height, row + 1, col, sol))   // Down
    {
      return 1;
    }

    // No valid path found, backtrack
    sol[row][col] = maze[row][col];
    return 0;
  }
  return 0;
}

// The function to generate a maze (given)
void genMaze(char maze[][200], const int maze_width, const int maze_height, const double threshold, const int seed)
{
  // set random seed
  srand(seed);
  // gen start and end positions
  int start_x = rand() % (maze_width - 2) + 1;
  int start_y = rand() % (maze_height - 2) + 1;
  int end_x = rand() % (maze_width - 2) + 1;
  int end_y = rand() % (maze_height - 2) + 1;
  // gen maze
  for (int r = 0; r < maze_height; ++r)
  {
    for (int c = 0; c < maze_width; ++c)
    {
      if (r == 0 || c == 0 || r == maze_height - 1 || c == maze_width - 1)
        maze[r][c] = '#';
      else if (c == start_x && r == start_y)
        maze[r][c] = '@';
      else if (c == end_x && r == end_y)
        maze[r][c] = '<';
      else
      {
        double rand_value = rand() / (double)RAND_MAX;
        if (rand_value >= threshold)
          maze[r][c] = '#';
        else
          maze[r][c] = ' ';
      }
    }
  }
}