// Copyright (c) 2020 [Swathi Ram]. All rights reserved.

#pragma once

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
   * Overridden function that does not take in a parameter if the grid has
   * stabilized. Used if the user has chosen to pause the automaton or if it
   * is the first call to the calculation of the configuration.
   */
  std::vector<std::vector<int>>& GetCurrentGrid();

  /*
   * Helper method to check which grid to use as the current vs. the next
   * generation. This method facilitates the ping pong effect between the two
   * grids. If the next generation should be calculated, an even id prompts the
   * calculated using the first grid as the current and the second as the next
   * generation to be added to. An odd id uses the next generation that was
   * previously calculated as the current and fills out the other grid with the
   * next generation of that grid.
   * @param did_gen_change_: bool to check whether the pattern has stabilized
   * @return: returns the grid containing the current cell configuration
   */
  std::vector<std::vector<int>>& GetCurrentGrid(bool& did_gen_change_);

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
  void SetDimensionAndFillSeeds(int dimension,
                                std::vector<std::vector<int>> seed);

  /*
   * Helper method to support restarting the automaton when the user chooses.
   * Clears the grids, setting all positions to 0.
   */
  void ResetGrid();

  /*
 * 3D vector containing both grids to allow for choosing certain grid
 * as the current grid vs. the next generation */
  std::vector<std::vector<std::vector<int>>> grids_;

 private:
  /*
   * Helper method to compare two grids for equality. Used to check when the
   * cell configuration has stabilized as the grids will be equal when no more
   * generations can be calculated.
   * @return: Boolean for if the grids are the same in each position
   */
  bool DidGridChange();

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

  /*
   * Helper method to count the number of surrounding cells around a particular
   * cell at the passed in location on the grid. Calculates neighbors by adding
   * the label of the cell (1 or 0).
   * @param grid: cell grid containing the cell configuration information
   * @param x: x coordinate of the cell
   * @param y: y coordinate of the cell
   * @return: method returns the numbers of neighbors of a particular cell
   */
  size_t CountNeighbors(std::vector<std::vector<int>>& grid, int x, int y);

  /* Private variable to store the passed in dimension of the grid */
  size_t grid_dimension_;

  /*
   * Continuously updates id of grids to allow for switching between the grid
   * of the current generation and the next generation. Is incremented every
   * time the next generation is calculated to allow for the current grid to
   * be updated as the cycle continues. */
  size_t gen_id_ = 0;
};

}  // namespace mylibrary
