// Copyright (c) 2020 [Swathi Ram]. All rights reserved.

#include "../include/mylibrary/grid.h"

#include <iostream>

namespace mylibrary {

/*
 * Overridden function that does not take in a parameter if the grid has
 * stabilized. Used if the user has chosen to pause the automaton or if it
 * is the first call to the calculation of the configuration.
 */
std::vector<std::vector<int>>& Grid::GetCurrentGrid() {
  return grids_[gen_id_ % 2];
}

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
std::vector<std::vector<int>>& Grid::GetCurrentGrid(bool& did_gen_change_) {
  if (gen_id_ % 2 == 0) {
    CalculateNextGeneration(grids_[0], grids_[1]);
  } else {
    CalculateNextGeneration(grids_[1], grids_[0]);
  }
  did_gen_change_ = DidGridChange();
  return grids_[gen_id_ % 2];
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
void Grid::SetDimensionAndFillSeeds(int dimension,
                                    std::vector<std::vector<int>> seed) {
  grid_dimension_ = dimension;

  // first level
  grids_.resize(2);

  // second level
  grids_[0].resize(dimension);
  grids_[1].resize(dimension);

  // third level
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < dimension; j++) {
      grids_[i][j].resize(dimension);
    }
  }

  for (int i = 0; i < seed.size(); i++) {
    assert((seed[i][0]) < grid_dimension_);
    assert((seed[i][1]) < grid_dimension_);
    grids_[0][seed[i][0]][seed[i][1]] = 1;
  }
}

/*
 * Helper method to compare two grids for equality. Used to check when the
 * cell configuration has stabilized as the grids will be equal when no more
 * generations can be calculated.
 * @return: Boolean for if the grids are the same in each position
 */
bool Grid::DidGridChange() {
  for (int i = 0; i < grid_dimension_; i++) {
    for (int j = 0; j < grid_dimension_; j++) {
      if (grids_[0][i][j] != grids_[1][i][j]) {
        return true;
      }
    }
  }
  return false;
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
        size_t num_neighbors = CountNeighbors(curr_gen_, i, j);
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
size_t Grid::CountNeighbors(std::vector<std::vector<int>>& grid, int x, int y) {
  size_t num_neighbors = 0;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      num_neighbors += grid[x + i][y + j];  // 0's and 1's so add for sum
    }
  }
  num_neighbors -= grid[x][y];
  return num_neighbors;
}

/*
 * Helper method to support restarting the automaton when the user chooses.
 * Clears the grids, setting all positions to 0.
 */
void Grid::ResetGrid() {
  for (int i = 0; i < grid_dimension_; i++) {
    for (int j = 0; j < grid_dimension_; j++) {
      grids_[0][i][j] = 0;
      grids_[1][i][j] = 0;
    }
  }
  gen_id_ = 0;
}

}  // namespace mylibrary
