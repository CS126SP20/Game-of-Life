// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "../include/mylibrary/grid.h"

namespace myapp {

/* Constant to represent the grid dimension and number of cells */
const size_t kGridDimension = 600;

/* Constant for dimension of each individual cell */
const size_t kCellDimension = 10;
const std::string kGlider = "../../../../../../resources/glider.json";
const std::string kSmallExploder = "../../../../../../resources/small_exploder.json";
const std::string kTenCellRow = "../../../../../../resources/ten_cell_row.json";

/* Constant for the numbers of cells in the grid */
const size_t kNumCells = kGridDimension / kCellDimension;

class MyApp : public cinder::app::App {
 public:
  /* Default Constructor */
  MyApp();

  /*
   * Method setting up the display and sets up the grid object to be set to
   * passed dimension and filled with the json coordinates
   */
  void setup() override;

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

 private:
  /* Grid object created to hold json coordinates */
  mylibrary::Grid grid_;

  /* This method deals with parsing the json file of the initial configuration
   * the user chooses. After opening the file, the coordinates are stored into
   * a vector and the grid object is populated with this information. The flag
   * for if a file was chosen is set to true to signify that the grid can be
   * created and drawn as the user has chosen to see a configuration.
   * @param file_name- name of file user chooses
   */
  void ParseFile(std::string file_name);

  /* Helper method to draw the empty grid and loop through to fill in the
   * live cells*/
  void drawFilledGrid(std::vector<std::vector<int>>& grid);

  /* Method in progress to draw buttons for the user to choose with initial
   * configurations of cells they want to see the automaton for */
  void DrawInitialScreen();

  /* Helper method to draw the textboxes on the screen for the user to choose
   * to pause, resume, or restart the automaton */
  void DrawOptions();

  /* Method to display text and add text boxes to GUI */
  void PrintText(const std::string& text, const cinder::Color color, const cinder::ivec2& size,
                 const cinder::vec2& loc);

  /* Boolean value to check if user chose a json file */
  bool Is_File_Chosen = false;

  /* Boolean value to check if user pauses the automaton */
  bool Is_Paused = false;

  /* Boolean value to check if the final state is reached */
  bool Is_Stabilized = false;

  size_t first_call = 0;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
