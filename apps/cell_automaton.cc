// Copyright (c) 2020 [Swathi Ram]. All rights reserved.

#include "cell_automaton.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/scoped.h>

#include <chrono>
#include <nlohmann/json.hpp>

#include "../include/mylibrary/grid.h"

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::app::KeyEvent;

const std::vector<std::string> kConfigurationNames{"Glider", "Small Exploder",
                                                   "Ten Cell Row"};
const size_t kFontSize = 25;
const std::string kGlider = "../../../../../../resources/glider.json";
const char kNormalFont[] = "Times New Roman";
const std::vector<std::string> kOptionNames{"Pause: 'p'", "Resume: 'r'",
                                            "Restart: 'x'"};
const std::string kSmallExploder =
    "../../../../../../resources/small_exploder.json";
const std::string kTenCellRow = "../../../../../../resources/ten_cell_row.json";
const Color kWhite = Color(255, 255, 255);

/* Default Constructor */
MyApp::MyApp() {}

/* This method deals with parsing the json file of the initial configuration
 * the user chooses. After opening the file, the coordinates are stored into
 * a vector and the grid object is populated with this information. The flag
 * for if a file was chosen is set to true to signify that the grid can be
 * created and drawn as the user has chosen to see a configuration.
 * @param file_name- name of file user chooses
 */
void MyApp::ParseFile(std::string file_name) {
  std::vector<std::vector<int>> filled_grid_;
  std::ifstream i(file_name, std::fstream::in);
  if (!i.is_open()) {
    std::cout << "Failed to Open File " << '\n';
    return;
  }
  if (i.fail()) {
    std::cout << "Error in File" << std::endl;
    return;
  }

  nlohmann::json j;
  i >> j;
  for (auto& x : j["seeds"].items()) {
    int num_x = x.value()["x"];
    int num_y = x.value()["y"];
    std::vector<int> coordinates = {num_x, num_y};

    filled_grid_.push_back(coordinates);
  }

  grid_.SetDimensionAndFillSeeds(kNumCells, filled_grid_);
  first_call = 0;
  Is_File_Chosen = true;
}

/*
 * Method setting up the display and sets up the grid object to be set to
 * passed dimension and filled with the json coordinates
 */
void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

/*
 * Method dealing with all the draw functionality throughout the project.
 * Calculates the delay to have time between the drawing of cell
 * configurations. Deals with which configuration to
 * draw depending on user's choice */
void MyApp::draw() {
  const cinder::vec2 center = getWindowCenter();

  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::clear(kWhite);

  DrawInitialScreen();
  bool did_gen_change = false;

  if (Is_File_Chosen) {
    cinder::gl::clear();
    cinder::gl::clear(kWhite);
    if (Is_Paused ||
        first_call == 0) {  // Is_Paused cannot be set before first call
      std::vector<std::vector<int>>& grid = grid_.GetCurrentGrid();
      drawFilledGrid(grid);
      if (first_call == 0) {
        first_call++;
      }
    } else {
      std::vector<std::vector<int>>& grid =
          grid_.GetCurrentGrid(did_gen_change);
      if (!did_gen_change) {
        Is_Stabilized = true;
        PrintText(
            "The pattern has stabilized.\n Press 'x' to see another automaton.",
            Color::black(), {300, 90}, {300, 520});
      }
      drawFilledGrid(grid);
    }
  }
}

/* Method in progress to draw buttons for the user to choose with initial
 * configurations of cells they want to see the automaton for */
void MyApp::DrawInitialScreen() {
  cinder::gl::color(0, 0, 0);
  const Color color = Color::black();
  const cinder::ivec2 size = {100, 60};
  cinder::vec2 location = {85, 355};

  PrintText(
      "Welcome to the Game of Life!\n Please press the number of the cell "
      "automaton\n you want to see:",
      color, {300, 150}, {300, 200});
  size_t x = 25;
  size_t y = 320;
  for (int i = 1; i < 4; i++) {
    cinder::gl::drawStrokedRect(Rectf(x, y, x + 170, y + 70));
    x += 190;
    PrintText(std::to_string(i) + ". " + kConfigurationNames[i - 1], color,
              size, location);
    location.x += 190;
  }
}

/* Helper method to draw the textboxes on the screen for the user to choose
 * to pause, resume, or restart the automaton */
void MyApp::DrawOptions() {
  const Color color = Color::black();
  const cinder::ivec2 size = {150, 40};
  cinder::vec2 location = {80, 635};
  size_t x = 25;
  size_t y = 610;
  for (int i = 0; i < 3; i++) {
    cinder::gl::drawStrokedRect(Rectf(x, y, x + 170, y + 40));
    x += 190;
    PrintText(kOptionNames[i], color, size, location);
    location.x += 200;
  }
}

/* Helper method to draw the empty grid and loop through to fill in the
 * live cells */
void MyApp::drawFilledGrid(std::vector<std::vector<int>>& grid) {
  for (int i = 0; i < kNumCells; i++) {
    for (int j = 0; j < kNumCells; j++) {
      int x_coord = i * 10;
      int y_coord = j * 10;
      if (grid[i][j] == 0) {
        cinder::gl::color(0, 0, 0);
        cinder::gl::drawStrokedRect(
            Rectf(x_coord, y_coord, x_coord + 10, y_coord + 10));
      } else {
        cinder::gl::color(255, 0, 0);
        cinder::gl::drawSolidRect(
            Rectf(x_coord, y_coord, x_coord + 10, y_coord + 10));
      }
    }
  }
  DrawOptions();
}

/* Method dealing with user choice of file. (in progress) checks if user
 * presses down on "1" key and eventually other numbers to choose json
 * file with initial configuration of cells */
void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_1: {
      ParseFile(kGlider);
      break;
    }
    case KeyEvent::KEY_2: {
      ParseFile(kSmallExploder);
      break;
    }
    case KeyEvent::KEY_3: {
      ParseFile(kTenCellRow);
      break;
    }
    case KeyEvent::KEY_p: {
      if (Is_File_Chosen && !Is_Stabilized) {
        Is_Paused = true;
      }
      break;
    }
    case KeyEvent::KEY_r: {
      Is_Paused = false;
      break;
    }
    case KeyEvent::KEY_x: {
      grid_.ResetGrid();
      cinder::gl::clear();
      Is_Paused = false;
      Is_File_Chosen = false;
      Is_Stabilized = false;
      break;
    }
  }
}

/* Method to display text and add text boxes to GUI */
void MyApp::PrintText(const std::string& text, const Color color,
                      const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = cinder::TextBox()
                 .alignment(cinder::TextBox::CENTER)
                 .font(cinder::Font(kNormalFont, kFontSize))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 location = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, location);
}

}  // namespace myapp