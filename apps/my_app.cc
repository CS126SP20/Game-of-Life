// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "my_app.h"

#include <cinder/app/App.h>


namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::Rectf;


MyApp::MyApp() {
  std::cout << "constructor called" << std::endl;
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  std::cout << "setup called" << std::endl;

}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::clear(Color(0, 50, 0));

  cinder::gl::drawSolidRect(Rectf(50 * 4,
                                  50 * 8,
                                  50 * 4 + 50,
                                  50 * 8 + 50));
  const cinder::vec2 center = getWindowCenter();
  std::cout << "draw called" << std::endl;
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
