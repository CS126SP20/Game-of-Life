// Copyright (c) 2020 [Swathi Ram]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cstddef>
#include <vector>
namespace mylibrary {

/*
 * Class dealing with the grid object containing the backend logic of filling
 * the cell grid with the json coordinates and calculated the cyclical next
 * generation of cells
 */
class Grid {
 public:
  /*
   * 3D vector containing both grids to allow for choosing certain grid
   * as the current grid vs. the next generation */
  std::vector<std::vector<std::vector<int>>> grids;

  // TODO comment
  std::vector<std::vector<int>>& Get_Curr_Grid();

  /*
   * Helper method to check which grid to use as the current vs. the next
   * generation. This method facilitates the ping pong effect between the two
   * grids. If the next generation should be calculated, an even id prompts the
   * calculated using the first grid as the current and the second as the next
   * generation to be added to. An odd id uses the next generation that was
   * previously calculated as the current and fills out the other grid with the
   * next generation of that grid.
   * @param calculate_next_gen: boolean to check whether next generation should
   * be calculated //TODO param
   * @return: returns the grid containing the current cell configuration
   */
  std::vector<std::vector<int>>& Get_Curr_Grid(bool& did_gen_change);

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
  void SetDimensionAndFillSeeds(size_t dimension,
                                std::vector<std::vector<int>> seed);
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
  void CalculateNextGeneration(std::vector<std::vector<int>>& curr_gen_,
                               std::vector<std::vector<int>>& next_gen_);
 private:
  /* Private variable to store the passed in dimension of the grid */
  size_t grid_dimension_;

  /*
   * Continuously updates id of grids to allow for switching between the grid
   * of the current generation and the next generation. Is incremented every
   * time the next generation is calculated to allow for the current grid to
   * be updated as the cycle continues. */
  size_t gen_id_ = 0;

  /*
   * Helper method to print out the grid after it has been filled with 1's
   * or 0's. Method is called in the helper method FillGrid.
   * @param passed_grid_: grid to be printed
   */
  void PrintGrid(std::vector<std::vector<int>> passed_grid_);

  // TODO comment
  bool DidGridChange();

  /*
   * Helper method to count the number of surrounding cells around a particular
   * cell at the passed in location on the grid. Calculates neighbors by adding
   * the label of the cell (1 or 0).
   * @param grid: cell grid containing the cell configuration information
   * @param x: x coordinate of the cell
   * @param y: y coordinate of the cell
   * @return: method returns the numbers of neighbors of a particular cell
   */
  int CountNeighbors(std::vector<std::vector<int>>& grid, int x, int y);
};

}  // namespace mylibrary

#endif  // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
