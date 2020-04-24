// Copyright (c) 2020 [Swathi Ram]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/scoped.h>

#include <nlohmann/json.hpp>

#include "../include/mylibrary/grid.h"

namespace myapp {

using cinder::Color;
using cinder::Rectf;
using cinder::app::KeyEvent;

MyApp::MyApp() {
  std::ifstream i("../../../../../../resources/small_exploder.json",
                  std::fstream::in);
  if (!i.is_open()) {
    std::cout << "failed to open file " << '\n';
    return;  // TODO error handling
  }
  if (i.fail()) {
    std::cout << "error" << std::endl;  // return to handle error
    return;                             // TODO error handling
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

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  mylibrary::Grid model_grid(60, filled_grid_);
  std::cout << "frame rate " << getFrameRate() << std::endl;
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::clear(Color(255, 255, 255));
  const cinder::vec2 center = getWindowCenter();
  drawGrid();
  drawLiveCells();
}

void MyApp::drawGrid() {
  cinder::gl::color(0, 0, 0);
  for (int i = 0; i < 600; i += 10) {
    for (int j = 0; j < 600; j += 10) {
      cinder::gl::drawStrokedRect(Rectf(i, j, i + 10, j + 10));
    }
  }
}

void MyApp::drawLiveCells() {
  cinder::gl::color(255, 0, 0);
  for (int i = 0; i < filled_grid_.size(); i++) {
    int x_coord = (filled_grid_[i][0]) * 10;
    int y_coord = (filled_grid_[i][1]) * 10;
    cinder::gl::drawSolidRect(
        Rectf(x_coord, y_coord, x_coord + 10, y_coord + 10));
  }
}

void MyApp::DrawNextGeneration() {

}

void MyApp::keyDown(KeyEvent event) {}

}  // namespace myapp
