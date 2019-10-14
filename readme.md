# C++ Boilerplate
[![Build Status](https://travis-ci.org/kartikmadhira1/human-detection-module.svg?branch=master)](https://travis-ci.org/kartikmadhira1/human-detection-module)
[![Coverage Status](https://coveralls.io/repos/github/kartikmadhira1/human-detection-module/badge.svg?branch=master)](https://coveralls.io/github/kartikmadhira1/human-detection-module?branch=master)
---

## Overview

The human detection module here will take a sequence of images from a video input and output
the bounding box coordinates for every human detected in the image and subsequently be used by
the robot to navigate or manipulate through space.

## Requirements

- `boost` version `1.58` or higher. 
- `OpenCV` version `3.1` or higher 
- `git`
- `cmake` version `2.8` or higher.
- `gcc` or `clang` that supports `std=c++11`.

## Build Instructions
```
git clone --recursive https://github.com/kartikmadhira1/human-detection-module
cd <path to repository>
mkdir build
cd build
cmake ..
make
```
## Running the module
```
Run tests: ./test/cpp-test
Run program: ./app/shell-app
```

## Building for code coverage
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```

## Product Backlog Schedule

The product backlog and iteration schedule can be seen [here](https://docs.google.com/spreadsheets/d/1X_c9bMi0b7AIUzMgMdLq84g2H6-rCiPsTc2X1IaxRng/edit?usp=sharing)