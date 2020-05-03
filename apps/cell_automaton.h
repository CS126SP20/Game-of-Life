// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "../include/mylibrary/grid.h"

namespace myapp {

/* Constant to represent the grid dimension and number of cells */
const size_t kgrid_dimension = 600;

/* Constant for dimension of each individual cell */
const size_t kcell_size = 10; //TODO naming
const std::string kGlider = "../../../../../../resources/glider.json";
const std::string kSmallExploder = "../../../../../../resources/small_exploder.json";
const std::string kTenCellRow = "../../../../../../resources/ten_cell_row.json";

/* //TODO not in use */
const size_t knum_cells = kgrid_dimension/kcell_size; //TODO format for const

class MyApp : public cinder::app::App {
 public:

  /*
   * Constructor dealing with reading from json file. Creates a json object,
   * reads coordinates from file, and fills a vector in with grid information */
  MyApp();

  /*
   * Method setting up the display and sets up the grid object to be set to
   * passed dimension and filled with the json coordinates
   */
  void setup() override;

  //TODO not in use
  void update() override;

  /*
   * Method dealing with all the draw functionality throughout the project.
   * Calculates the delay to have time between the drawing of cell
   * configurations. (in progress) will deal with which configuration to
   * draw depending on user's choice */
  void draw() override;

  /* Method dealing with user choice of file. (in progress) checks if user
   * presses down on "1" key and eventually other numbers to choose json
   * file with initial configuration of cells */
  void keyDown(cinder::app::KeyEvent) override;

  /* Method to display text and add text boxes to GUI */
  void PrintText(const std::string& text, const cinder::Color color, const cinder::ivec2& size,
                 const cinder::vec2& loc);

  /* Boolean value to check if user chose a json file */
  bool Is_File_Chosen = false;
 private:
  /* Grid object created to hold json coordinates */
  mylibrary::Grid grid_;

  /* //TODO */
  void ParseFile(std::string file_name);
  /* Helper method to draw the empty grid and loop through to fill in the
   * live cells*/
  void drawGrid(std::vector<std::vector<int>>& grid);

//  void drawLiveCells(std::vector<std::vector<int>>& grid);

  /* Method in progress to draw buttons for the user to choose with initial
   * configurations of cells they want to see the automaton for */
  void DrawInitialScreen();

  /* // TODO not in use*/
  std::vector<std::vector<int> > filled_grid_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
