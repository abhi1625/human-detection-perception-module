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

/**@file FrameTransformTest.cpp
 * @brief Test source file for frame transform module.
 *        Contains the tests for the defined methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 20, 2019
 */

#include <gtest/gtest.h>
#include "../include/ImageInference.hpp"
#include "../include/IOModule.hpp"
#include "../include/FrameTransform.hpp"

/**
 *@brief Test for image to camera frame transformation method. 
 *       Tests the size of the output returned after transforming bounding box
 *       coordinates from image to camera frame. 
 */
TEST(frameTransformCheck, testShapeimgToCam) {
    ImageInference infer;
    IOModule iomodule;
    FrameTransform ft;
    Mat image = iomodule.readImage("../data/testImage.jpg", false);
    infer.setModelParams();
    vector<Mat> finalLayerOut = infer.runForwardPass(image);
    infer.applyNMS(image, finalLayerOut);
    vector<cv::Rect> boxes = infer.getBoxes();
    ft.imageToCamera(boxes);
    Mat output = ft.getCoordsCam();
    uint8_t reqOutput = 3;
    ASSERT_EQ(output.rows, reqOutput);
}

/**
 *@brief Test for camera to Base frame method. 
 *       Tests the output dimension returned after transforming bounding box 
 *       coordinates from camera frame to robot's base frame.      
 */
TEST(camToBaseCheck, testShapeCamtoBase) {
    ImageInference infer;
    IOModule iomodule;
    FrameTransform ft;
    Mat image = iomodule.readImage("../data/testImage.jpg", false);
    infer.setModelParams();
    vector<Mat> finalLayerOut = infer.runForwardPass(image);
    infer.applyNMS(image, finalLayerOut);
    vector<cv::Rect> boxes = infer.getBoxes();
    ft.imageToCamera(boxes);
    Mat _output = ft.getCoordsCam();
    ft.cameraToBase();
    Mat output = ft.getCoords3D();
    uint8_t reqOutput = 4;
    ASSERT_EQ(output.rows, reqOutput);
}

/**
 *@brief Test for outputCoords method. 
 *       Tests that the method returns expected value after all transformations.      
 */
TEST(outputCoordsCheck, testOutputShape) {
    FrameTransform transform;
    cv::Rect rect(0, 120, 240, 360);
    vector<cv::Rect> rectVector{rect};
    vector<vector<float>> reqOutputs = transform.outputCoords(rectVector);
    ASSERT_EQ(reqOutputs[0][0], 0);
    ASSERT_EQ(reqOutputs[0][1], 120);
    ASSERT_EQ(reqOutputs[0][3], 240);
    ASSERT_EQ(reqOutputs[0][4], 360);
}