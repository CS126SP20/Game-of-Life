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
Grid::Grid(size_t dimension, std::vector<std::vector<int> > seed) {
  // want grid to be a global public variable
  // how to initialize with a passed in size
  grid_dimension_ = dimension;
  cell_grid_.resize(dimension);
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cell_grid_[i].resize(dimension);
    }
  }
  FillGrid(seed);
}

/*
 * Helper method to populate the global variable for the cell grid with the
 * coordinates passed in from the seed. In every existing coordinate in the
 * seed, a "1" is placed at that position in the cell grid. If there is no
 * coordinate for a position in the cell grid, the space is filled with a "0".
 * @param seed- the 2D vector containing the coordiates of the cells from the
 * json file
 */
void Grid::FillGrid(std::vector<std::vector<int> > seed) {
  std::cout << "the seed vector " << std::endl;
  for (int i = 0; i < seed.size(); i++) {
    std::cout << seed[i][0] << " " << seed[i][1] << " ";
    std::cout << std::endl;
  }

  for (int i = 0; i < seed.size(); i++) {
    assert((seed[i][0]) < grid_dimension_);
    assert((seed[i][1]) < grid_dimension_);
    std::cout << "i 0= " << seed[i][0] << " i 1= " << seed[i][1] << std::endl;
    cell_grid_[seed[i][1]][seed[i][0]] = 1;  // TODO isn't this flipped???
  }
  //  PrintGrid();
}

/*
 * Helper method to print out the grid after it has been filled with 1's
 * or 0's. Method is called in the helper method FillGrid.
 */
void Grid::PrintGrid() {
  for (int i = 0; i < cell_grid_.size(); i++) {
    for (int j = 0; j < cell_grid_.size(); j++) {
      std::cout << cell_grid_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

}  // namespace mylibrary
