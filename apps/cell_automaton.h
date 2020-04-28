// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include "../include/mylibrary/grid.h"

namespace myapp {

const size_t kgrid_dimension = 600;
const size_t kcell_size = 10;
const size_t knum_cells = kgrid_dimension/kcell_size;

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void PrintText(const std::string& text, const cinder::Color color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  bool Is_File_Chosen = false;
 private:
  mylibrary::Grid grid_;
  void drawGrid(std::vector<std::vector<int>>& grid);
  void drawLiveCells(std::vector<std::vector<int>>& grid);
  void DrawOptions();
  std::vector<std::vector<int> > filled_grid_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
