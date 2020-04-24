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
  next_gen_.resize(dimension);
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      cell_grid_[i].resize(dimension);
      next_gen_[i].resize(dimension);
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
    cell_grid_[seed[i][1]][seed[i][0]] = 1;  // TODO isn't this flipped???
  }
//  std::cout << "original grid: " << std::endl;
//  PrintGrid(cell_grid_);
  CalculateNextGeneration();
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

void Grid::CalculateNextGeneration() {
  std::cout << "called calulate next gen " << std::endl;
  /*
   * 1. Any live cell with fewer than two live neighbours dies, as if by
   * underpopulation.
   * 2. Any live cell with two or three live neighbours lives on to the next
   * generation.
   * 3. Any live cell with more than three live neighbours dies, as if by
   * overpopulation.
   * 4. Any dead cell with exactly three live neighbours becomes a live cell, as
   * if by reproduction.
   */
  for (int i = 0; i < cell_grid_.size(); i++) {
    for (int j = 0; j < cell_grid_.size(); j++) {
      int state = cell_grid_[i][j];
      // account for edge cells
      if (i == 0 || i == cell_grid_.size() - 1 || j == 0 ||
          j == cell_grid_.size() - 1) {
        next_gen_[i][j] = state;
      } else {
        int num_neighbors = CountNeighbors(i, j);
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
//  std::cout << "next generation grid: " << std::endl;
//  PrintGrid(next_gen_);
//  cell_grid_ = next_gen_;
}

int Grid::CountNeighbors(int x, int y) {
  int num_neighbors = 0;
  for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
          num_neighbors += cell_grid_[x + i][y + j]; // 0's and 1's so add for sum
      }
  }
  num_neighbors -= cell_grid_[x][y];
  return num_neighbors;
}

}  // namespace mylibrary
