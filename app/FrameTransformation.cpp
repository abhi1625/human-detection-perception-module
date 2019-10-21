/******************************************************************************
 *  MIT License
 *
 *  Copyright (c) 2019 Kartik Madhira, Abhinav Modi 

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

/**@file Frametransform.hpp
 * @brief Source file for frame-transform module to convert detection outputs
 *        to useful information in the robot's reference frame. Contains 
 *        implementations for required methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 21, 2019
 */
#include "../include/FrameTransform.hpp"

FrameTransform::FrameTransform() {
}

void FramTransform::imageToCamera(const vector<cv::Rect> &Boxes) {
    // Define a matrix for camera intrinsics - assumed identity for now
    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat cameraMatrixInv = cameraMatrix.inv();
    // Convert vector of boxes to a matrix with box coordinates
    for (auto &box : Boxes) {
        vector<int> v{box.x, box.y, 1};
        cv::Mat _row(1, v.size(), CV_64F, v.data()); 
        cv::vconcat(coordsCam, _row, coordsCam);
    }
    coordsCam = coordsCam.t();
    // Convert box coordinates from image to camera matrix
    coordsCam = cameraMatrixInv * coordsCam;
}

void FrameTransform::cameraToBase() {
    // define a Transformation matrix between camera and robot's base frame
    // assumed identity for now
    cv::Mat camToBase = cv::Mat::eye(4, 4, CV_64F);

    coords3D = coordsCam;
    cv::Mat row = cv::Mat::ones(1, coords3D.cols, CV_64F);
    cv::vconcat(coords3D, row, coords3D);

    // transform coords to robot's base frame
    coords3D = camToBase * coords3D;
}

cv::Mat FrameTransform::getCoords3D() {
    cv::Mat _coords3D = this->coords3D;
    return _coords3D;
}

cv::Mat FrameTransform::getCoordsCam() {
    cv::Mat _coordsCam = this->coordsCam;
    return _coordsCam;
}

vector<vector<float>> FrameTransform::outputCoords(const vector<cv::Rect> &Boxes) {
    // store the output of coordinates in x, y, z, w, h
    vector<vector<float>> _outputCoords;
    for (auto &eachBox : Boxes) {
        float x = eachBox.x;
        float y = eachBox.y;
        float z = 1.0;
        float w = eachBox.width;
        float h = eachBox.height;
        vector<float> v = {x,y,z,w,h};
        _outputCoords.push_back(v);
    }
    return _outputCoords;
}

FrameTransform::~FrameTransform() {
}