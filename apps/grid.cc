// Copyright (c) 2020 [Swathi Ram]. All rights reserved.

#include "../include/mylibrary/grid.h"

#include <iostream>

namespace mylibrary {

/*
 * Constructor for the grid class. Resizes the cell grid to the dimensions
 * that are passed in and calls helper method to fill the grid with the passed
 * in coordinates from the json file stored in the 2D vector.
 * @param dimension- the size of the dimension by dimension grid
 * @param seed- the 2D vector containing the coordiates of the cells from the
 * json file
 */

// TODO ensure dimension is set before this call

std::vector<std::vector<int> >& Grid::Get_Curr_Grid(bool calc_next_gen) {
  if (calc_next_gen) {
    if (gen_id_ % 2 == 0) {
      CalculateNextGeneration(grids[0], grids[1]);
    } else {
      CalculateNextGeneration(grids[1], grids[0]);
    }
  }
  return grids[gen_id_ % 2];
}

/*
 * Helper method to populate the global variable for the cell grid with the
 * coordinates passed in from the seed. In every existing coordinate in the
 * seed, a "1" is placed at that position in the cell grid. If there is no
 * coordinate for a position in the cell grid, the space is filled with a "0".
 * @param seed- the 2D vector containing the coordiates of the cells from the
 * json file
 */
void Grid::SetDimensionAndFillSeeds(size_t dimension, std::vector<std::vector<int> > seed) {
  grid_dimension_ = dimension;

  // first level
  grids.resize(2); //TODO magic #

  // second level
  grids[0].resize(dimension);
  grids[1].resize(dimension);

  // third level
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < dimension; j++) {
      grids[i][j].resize(dimension);
    }
  }
  std::cout << "the seed vector " << std::endl;
  for (int i = 0; i < seed.size(); i++) {
    std::cout << seed[i][0] << " " << seed[i][1] << " ";
    std::cout << std::endl;
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
 */
void Grid::PrintGrid(std::vector<std::vector<int> > passed_grid_) { //TODO pass in any grid as parameter
  for (int i = 0; i < passed_grid_.size(); i++) {
    for (int j = 0; j < passed_grid_.size(); j++) {
      std::cout << passed_grid_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void Grid::CalculateNextGeneration(std::vector<std::vector<int> >& curr_gen_, std::vector<std::vector<int> >& next_gen_) {

  std::cout << "called calulate next gen " << std::endl;
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
//  std::cout << "next generation grid: " << std::endl;
//  PrintGrid(next_gen_);
//  cell_grid_ = next_gen_;
}

int Grid::CountNeighbors(std::vector<std::vector<int> >& grid, int x, int y) {
  int num_neighbors = 0;
  for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
          num_neighbors += grid[x + i][y + j]; // 0's and 1's so add for sum
      }
  }
  num_neighbors -= grid[x][y];
  return num_neighbors;
}

}  // namespace mylibrary
