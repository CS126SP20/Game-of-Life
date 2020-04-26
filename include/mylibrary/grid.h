// Copyright (c) 2020 [Swathi Ram]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cstddef>
#include <vector>
namespace mylibrary {

/*
 * CLASS COMMENT
 */
class Grid {
 public:
  /*
  * Constructor for the grid class. Resizes the cell grid to the dimensions
  * that are passed in and calls helper method to fill the grid with the passed
  * in coordinates from the json file stored in the 2D vector.
  * @param dimension- the size of the dimension by dimension grid
  * @param seed- the 2D vector containing the coordiates of the cells from the
  * json file
  */
//  Grid(size_t dimension, std::vector<std::vector<int> > seed);

  /* 2D vector to be populated with 1's and 0's in accordance to the
   * coordinates passed in by the seed vector from the json file
   */
//  std::vector<std::vector<int> > grid_a_;
//  std::vector<std::vector<int> > grid_b_;
  std::vector<std::vector<std::vector<int>>> grids;
  /*
  * //TODO
  */
  void CalculateNextGeneration(std::vector<std::vector<int> >& curr_gen_, std::vector<std::vector<int> >& next_gen_);

  /* //TODO make private again
  * Helper method to print out the grid after it has been filled with 1's
  * or 0's. Method is called in the helper method FillGrid.
  */
  void SetDimensionAndFillSeeds(size_t dimension, std::vector<std::vector<int> > seed);
  std::vector<std::vector<int> >& Get_Curr_Grid(bool calc_next_gen);
 private:
  /* Private variable to store the passed in dimension */
  size_t grid_dimension_;
  size_t gen_id_ = 0;
  /*
  * Helper method to populate the global variable for the cell grid with the
  * coordinates passed in from the seed. In every existing coordinate in the
  * seed, a "1" is placed at that position in the cell grid. If there is no
  * coordinate for a position in the cell grid, the space is filled with a "0".
  * @param seed- the 2D vector containing the coordiates of the cells from the
  * json file
  */
  void PrintGrid(std::vector<std::vector<int> > passed_grid_);


  /*
   * //TODO
   */
  int CountNeighbors(std::vector<std::vector<int> >& grid, int x, int y);
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
