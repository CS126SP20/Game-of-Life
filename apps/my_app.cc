// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/scoped.h>

#include <nlohmann/json.hpp>
#include "../include/mylibrary/grid.h"

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::Rectf;

MyApp::MyApp() {
//  std::ifstream i("test_seeds.json");
  std::ifstream i("../../../../../../resources/seeds.json", std::fstream::in);
  if (!i.is_open()) {
    std::cout << "failed to open file " << '\n';
    return; //TODO error handling
  }
  if (i.fail()) {
    std::cout << "error" << std::endl;  // return to handle error
    return; //TODO error handling
  }
    nlohmann::json j;
    i >> j;
    std::cout << "json content:" << std::endl << j.at("seeds").at(0).at("x") << std::endl;


  std::vector<std::vector<int> > cell_grid; //TODO USE PUSHBACK AND FOR EACH
//  for (int i = 0; i < 3; i++) {
//    cell_grid[i][0] = j.at("seeds").at(i).at("x");
//    cell_grid[i][1] = j.at("seeds").at(i).at("y");
//  }
//  std::cout << "cell grid size =  " << cell_grid.size() << std::endl;
//
//  std::cout << "my loading json to vector " << std::endl;
//  for (int i = 0; i < cell_grid.size(); i++) {
//    std::cout << cell_grid[i][0] << " " << cell_grid[i][1] << " ";
//    std::cout << std::endl;
//  }

  for (auto& x : j["seeds"].items())
  {
//    cell_grid[x.key()].push_back(x.value());
    int num_x =  x.value()["x"];
    int num_y =  x.value()["y"];
    std::vector<int> coordinates = {num_x, num_y};
    cell_grid.push_back(coordinates);
//    std::cout << "key: " << x.key() << ", x value: " << x.value()["x"] << ". y value: " << x.value()["y"] << '\n';
    std::cout << "x is " << num_x << " y is " << num_y << std::endl;
  }

  std::cout << "json coordinates " << std::endl;
  for (int i = 0; i < cell_grid.size(); i++) {
    std::cout << cell_grid[i][0] << " " << cell_grid[i][1] << " ";
    std::cout << std::endl;
  }
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  mylibrary::Grid model_grid(10);
}

void MyApp::update() { }

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
  for (int i = 0; i < 800; i+= 40) {
    for (int j = 0; j < 800; j+= 40) {
      cinder::gl::drawStrokedRect(Rectf(i, j, i + 40, j + 40));
    }
  }
}

void MyApp::drawLiveCells() {
  std::vector<int> values{40, 160, 320, 120};
  for (auto loc : values) {
    cinder::gl::color(255, 0, 0);
    cinder::gl::drawSolidRect(Rectf(loc, loc, loc + 40, loc + 40));
  }
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
