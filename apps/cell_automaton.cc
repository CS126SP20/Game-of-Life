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

const Color kWhite = Color(255, 255, 255);
const size_t kFontSize = 15;
const char kNormalFont[] = "Times New Roman";

/*
 * Constructor dealing with reading from json file. Creates a json object,
 * reads coordinates from file, and fills a vector in with grid information */
MyApp::MyApp() {
  std::ifstream i("../../../../../../resources/small_exploder.json",
                  std::fstream::in);
  if (!i.is_open()) {
    std::cout << "failed to open file " << '\n';
    return;  // TODO error handling
  }
  if (i.fail()) {
    std::cout << "error" << std::endl;
    return;
  }
  nlohmann::json j;
  i >> j;
  std::cout << "json content:" << std::endl
            << j.at("seeds").at(0).at("x") << std::endl;

  for (auto& x : j["seeds"].items()) {
    int num_x = x.value()["x"];
    int num_y = x.value()["y"];
    std::vector<int> coordinates = {num_x, num_y};

    filled_grid_.push_back(coordinates);
    std::cout << "x is " << num_x << " y is " << num_y << std::endl;
  }

  std::cout << "json coordinates " << std::endl;
  for (int i = 0; i < filled_grid_.size(); i++) {
    std::cout << filled_grid_[i][0] << " " << filled_grid_[i][1] << " ";
    std::cout << std::endl;
  }
}

/*
 * Method setting up the display and sets up the grid object to be set to
 * passed dimension and filled with the json coordinates
 */
void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  grid_.SetDimensionAndFillSeeds(knum_cells, filled_grid_);
  std::cout << "frame rate " << getFrameRate() << std::endl;
}

void MyApp::update() {}

/*
 * Method dealing with all the draw functionality throughout the project.
 * Calculates the delay to have time between the drawing of cell
 * configurations. (in progress) will deal with which configuration to
 * draw depending on user's choice */
void MyApp::draw() {
  static int delay_count = 0;
  static int first_call = 0;
  if (delay_count % 2 != 0) {
    delay_count++;
    return;
  }
  delay_count++;
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::clear(kWhite);
  const cinder::vec2 center = getWindowCenter();
  DrawOptions();
  if (Is_File_Chosen) {
    cinder::gl::clear();
    cinder::gl::clear(kWhite);
    std::vector<std::vector<int>>& grid = grid_.Get_Curr_Grid(first_call != 0);
    first_call++;
    drawGrid(grid);
  }
  auto time = std::chrono::system_clock::now();
}

/* Method in progress to draw buttons for the user to choose with initial
 * configurations of cells they want to see the automaton for */
void MyApp::DrawOptions() {
  cinder::gl::color(0, 0, 0);
  const Color color = Color::black();
  const cinder::vec2 location = {60, 625};
  const cinder::ivec2 size = {70, 20};
  PrintText("1. glider", color, size, location);
  size_t x = 20;
  size_t y = 610;
  for (int i = 0; i < 3; i++) {
    cinder::gl::drawStrokedRect(Rectf(x, y, x + 100, y + 30));
    x += 140;
  }
}

/* Helper method to draw the empty grid and loop through to fill in the
 * live cells*/
void MyApp::drawGrid(std::vector<std::vector<int>>& grid) {
  for (int i = 0; i < knum_cells; i++) {
    for (int j = 0; j < knum_cells; j++) {
      int x_coord = i * 10;
      int y_coord = j * 10;
      if (grid[i][j] == 0) {
        cinder::gl::color(0, 0, 0);
        cinder::gl::drawStrokedRect(
            Rectf(x_coord, y_coord, x_coord + 10, y_coord + 10));
      } else {
        cinder::gl::color(255, 0, 0);
        cinder::gl::drawSolidRect(Rectf(x_coord, y_coord, x_coord + 10,
                                        y_coord + 10));  // TODO border missing
      }
    }
  }
}

/* Method dealing with user choice of file. (in progress) checks if user
 * presses down on "1" key and eventually other numbers to choose json
 * file with initial configuration of cells */
void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_1: {
      Is_File_Chosen = true;
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
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}  // namespace myapp

}  // namespace myapp