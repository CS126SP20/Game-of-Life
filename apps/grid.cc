// Copyright (c) 2020 [Swathi Ram]. All rights reserved.

#include "../include/mylibrary/grid.h"

#include <iostream>

namespace mylibrary {

// TODO ensure dimension is set before this call

/*
 * Helper method to check which grid to use as the current vs. the next
 * generation. This method facilitates the ping pong effect between the two
 * grids. If the next generation should be calculated, an even id prompts the
 * calculated using the first grid as the current and the second as the next
 * generation to be added to. An odd id uses the next generation that was
 * previously calculated as the current and fills out the other grid with the
 * next generation of that grid.
 * @param calculate_next_gen: boolean to check whether next generation should
 * be calculated
 * @return: returns the grid containing the current cell configuration
 */
std::vector<std::vector<int>>& Grid::Get_Curr_Grid(bool calculate_next_gen) {
  if (calculate_next_gen) {
    if (gen_id_ % 2 == 0) {
      CalculateNextGeneration(grids[0], grids[1]);
    } else {
      CalculateNextGeneration(grids[1], grids[0]);
    }
  }
  return grids[gen_id_ % 2];
}

/*
 * Helper method to resize the 3D vector of grids and fill in the grid's cell
 * configuration based on the coordinates from the json file read into seed
 * from cell_automaton.cc. The dimension of the 3D vector dealing with the
 * grids is resized to 2 to account for the current and next generation of
 * cells. The next two dimensions are resized to the passed in dimensions. The
 * cell configuration is set to 1 if a cell exists at the coordinate and is kept
 * as 0 if not.
 * @param dimension: passed in size of the grid
 * @param seed: vector containing coordinates of cells from json file
 */
void Grid::SetDimensionAndFillSeeds(size_t dimension,
                                    std::vector<std::vector<int>> seed) {
  grid_dimension_ = dimension;

  // first level
  grids.resize(2);  // TODO magic #

  // second level
  grids[0].resize(dimension);
  grids[1].resize(dimension);

  // third level
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < dimension; j++) {
      grids[i][j].resize(dimension);
    }
  }

  for (int i = 0; i < seed.size(); i++) {
    assert((seed[i][0]) < grid_dimension_);
    assert((seed[i][1]) < grid_dimension_);
    grids[0][seed[i][0]][seed[i][1]] = 1;
  }
}

/*
 * Helper method to print out the grid after it has been filled with 1's
 * or 0's. Method is called in the helper method FillGrid.
 * @param passed_grid_: grid to be printed
 */
void Grid::PrintGrid(std::vector<std::vector<int>> passed_grid_) { //TODO can use size_t instead for vector
  for (int i = 0; i < passed_grid_.size(); i++) {
    for (int j = 0; j < passed_grid_.size(); j++) {
      std::cout << passed_grid_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/*
 * Helper method dealing with the main logic of calculating the next generation
 * of cells. Method is passed in two grids- the current generation of cells to
 * use for cell information and the next generation to be calculated and filled
 * in with the cells at their calculated position. The calculations follow the
 * fundamental rules of the Game of life:
 * 1. Any live cell with fewer than two live neighbours dies.
 * 2. Any live cell with two or three live neighbours lives.
 * 3. Any live cell with more than three live neighbours dies.
 * 4. Any dead cell with exactly three live neighbours becomes a live cell.
 * At the end of the method, the gen_id_ is incremented to
 * allow the switch between grids by the next call.
 * @param curr_gen_: current generation of cell configurations
 * @param next_gen_: next generation of cell configurations
 */
void Grid::CalculateNextGeneration(std::vector<std::vector<int>>& curr_gen_,
                                   std::vector<std::vector<int>>& next_gen_) {
  for (int i = 0; i < curr_gen_.size(); i++) {
    for (int j = 0; j < curr_gen_.size(); j++) {
      int state = curr_gen_[i][j];
      // account for edge cells
      if (i == 0 || i == curr_gen_.size() - 1 || j == 0 ||
          j == curr_gen_.size() - 1) {
        next_gen_[i][j] = state;
      } else {
        int num_neighbors = CountNeighbors(curr_gen_, i, j);
        if (state == 1 && num_neighbors < 2) {
          next_gen_[i][j] = 0;
        } else if (state == 1 && num_neighbors > 3) {
          next_gen_[i][j] = 0;
        } else if (state == 0 && (num_neighbors == 3)) {
          next_gen_[i][j] = 1;
        } else {
          next_gen_[i][j] = state;
        }
      }
    }
  }
  gen_id_++;
}

/*
 * Helper method to count the number of surrounding cells around a particular
 * cell at the passed in location on the grid. Calculates neighbors by adding
 * the label of the cell (1 or 0).
 * @param grid: cell grid containing the cell configuration information
 * @param x: x coordinate of the cell
 * @param y: y coordinate of the cell
 * @return: method returns the numbers of neighbors of a particular cell
 */
int Grid::CountNeighbors(std::vector<std::vector<int>>& grid, int x, int y) {
  int num_neighbors = 0; //tODO size_t
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      num_neighbors += grid[x + i][y + j];  // 0's and 1's so add for sum
    }
  }
  num_neighbors -= grid[x][y];
  return num_neighbors;
}

}  // namespace mylibrary
