// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <ctime>

#include "my_app.h"

/* Visualization of game:
 * https://bitstorm.org/gameoflife/ */

using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setResizable(false);
  settings->setTitle("Game of Life");

  std::srand(std::time(0));
  std::cout << "main set up called" << std::endl;

}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)

//CINDER_APP(myapp::MyApp, RendererGl)
