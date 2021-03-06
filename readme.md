# Human Detection Perception Module
[![Build Status](https://travis-ci.org/kartikmadhira1/human-detection-perception-module.svg?branch=master)](https://travis-ci.org/kartikmadhira1/human-detection-perception-module)
[![Coverage Status](https://coveralls.io/repos/github/kartikmadhira1/human-detection-perception-module/badge.svg?branch=master)](https://coveralls.io/github/kartikmadhira1/human-detection-perception-module?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---

## Overview

The human detection module here will take a sequence of images from a video input and output
the bounding box coordinates for every human detected in the image and subsequently be used by
the robot to navigate or manipulate through space.

This repository contains the implementation of the Human Detection module. The detection module takes inputs in the form of image sequences, video, camera feed and outputs the location of the detected humans in the robot’s inertial reference frame. The module also generates a text file containing the 3D coordinates of the detected human obstacles, the dimensions of the bounding box, frame ID and a label for each human detected in the frame. The module uses a YOLOv3 network trained on COCO dataset to make the predictions. The output format of the module allows further integration with other task-specific modules (such as a path-planning or controls module) which utilize the detection information.

In this project we have emphasized more on the preprocessing and the post processing of the data such that it can be integrated with other modules without any complications. For the current implementation we have assumed that the transformation between the camera and the robot's reference frame is an identity transform.

## Outputs
The output of the network is shown below for a test image. An output on a surveillence video is also included in the repo(in test/testResults) and the detections clearly indicate that with some tweaks this module can be deployed for many tasks such as human tracking, counting humans, etc.

![output](data/output/outputImage2.png )

## Requirements

- `boost` version `1.58` or higher. 
- `OpenCV` version `3.4.2` or higher 
- `git`
- `cmake` version `2.8` or higher.
- `gcc` or `clang` that supports `std=c++11`.
- Google Test: Unit test requires gtest framework by Google

## Build Instructions
```
git clone --recursive https://github.com/kartikmadhira1/human-detection-perception-module
cd <path to repository>
mkdir build
cd build
cmake ..
make
```
## Dependencies installation instructions
```
  git clone https://github.com/opencv/opencv.git
  cd opencv
  git checkout 3.4.2
  cd ..

  git clone https://github.com/opencv/opencv_contrib.git
  cd opencv_contrib
  git checkout 3.4.2
  cd ..

  cd opencv
  mkdir build
  cd build
  cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
  make -j$(nproc)
  sudo make install
  sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
  sudo ldconfig
  cd ../../

  pip install --user cpp-coveralls
  sudo apt-get install libopencv-dev
  sudo apt-get install libboost-all-dev

```
## Running the module
#### Running the demo
Once you have successfully built the package, go to the build folder and run:
```
./app/shell-app
```
When the program asks to enter `Input type` press `4`. This will use the default input nad output directories and run the demo. 
**Note:** Press any key to continue once an image is displayed.

#### Running the app and tests
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
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Generating Docs using Doxygen
- To install Doxygen
```
sudo apt get install doxygen
```
To generate documentation use
```
doxygen ./Doxygen
```

## Product Backlog Schedule
[![Backlog: AIP](https://img.shields.io/badge/Backlog-AIP-green.svg)](https://docs.google.com/spreadsheets/d/1X_c9bMi0b7AIUzMgMdLq84g2H6-rCiPsTc2X1IaxRng/edit?usp=sharing)

Agile Iterative Process was followed while developing this software package. The product backlog and iteration schedules can be seen [here](https://docs.google.com/spreadsheets/d/1X_c9bMi0b7AIUzMgMdLq84g2H6-rCiPsTc2X1IaxRng/edit?usp=sharing).

For more details on how the work was carried out, see the [sprint planning sheet](https://docs.google.com/document/d/1Q4IzRsmCA4za4dVSOyH8GB7yYPHi8W1GhDoZ9FRJOMo/edit?usp=sharing).

## About the authors
 - [Abhinav Modi](https://github.com/abhi1625) - Graduate student pursuing Masters of Engg. in Robotics at University of Maryland. Here is a link to my [website](abhi1625.github.io) where you can view some of my other projects.
 - [Kartik Madhira](https://github.com/kartikmadhira1) - Graduate student pursuing Masters of Engg. in Robotics at University of Maryland. Here is a link to my [website](kartikmadhira1.github.io) where you can view some of my other projects.
