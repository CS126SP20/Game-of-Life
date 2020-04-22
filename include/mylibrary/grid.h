// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cstddef>
#include <vector>
namespace mylibrary {

class Grid {
 public:
  // Empty constructor for image class
  Grid(size_t dimension, std::vector<std::vector<int> > seed);
  std::vector<std::vector<int> > cell_grid_;
 private:
  size_t grid_dimension_;
  void FillGrid(std::vector<std::vector<int> > seed);
  void PrintGrid();
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
