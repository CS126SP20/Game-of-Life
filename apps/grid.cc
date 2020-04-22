// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "../include/mylibrary/grid.h"

#include <iostream>

namespace mylibrary {

// in final, takes in dimension and seed from json (add parameter)
Grid::Grid(size_t dimension, std::vector<std::vector<int> > seed) {
  //want grid to be a global public variable
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

// does not need any parameter of dimension
// does not let to use cell_grid[][]
void Grid::FillGrid(std::vector<std::vector<int> > seed) {
//  std::vector<std::vector<int> > cell_grid(dimension, std::vector<int> (dimension, 0));
//  std::vector<std::vector<int> > seed{{1,2}, {2, 4}, {3, 3}};

  std::cout << "the seed vector " << std::endl;
  for (int i = 0; i < seed.size(); i++) {
    std::cout << seed[i][0] << " " << seed[i][1] << " ";
    std::cout << std::endl;
  }

  for (int i = 0; i < seed.size(); i++) {
    assert((seed[i][0]) < grid_dimension_);
    assert((seed[i][1]) < grid_dimension_);
    std::cout << "i 0= " << seed[i][0] << " i 1= " << seed[i][1] << std::endl;
    cell_grid_[seed[i][1]][seed[i][0]] = 1; //TODO isn't this flipped???
  }
//  PrintGrid();
}

// pass in the 2d grid
void Grid::PrintGrid() {
  for (int i = 0; i < cell_grid_.size(); i++) {
    for (int j = 0; j < cell_grid_.size(); j++) {
      std::cout << cell_grid_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

}  // namespace mylibrary
