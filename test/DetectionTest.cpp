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

/**@file DetectionTest.cpp
 * @brief Test source file for image-inference module.
 *        Contains the tests for the defined methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi, Kartik Madhira
 * @created on : Oct 20, 2019
 */

#include <gtest/gtest.h>
#include "../include/ImageInference.hpp"
#include "../include/IOModule.hpp"

/**
 *@brief Test for setModelParams method. 
 *       Tests if the method throws any exceptions. 
 */
TEST(intialParamLoadCheck, testInitalization) {
    ImageInference infer;
    EXPECT_NO_THROW(infer.setModelParams());
}

/**
 *@brief Test for runForwardPass method. 
 *       Tests that size of the output for forward pass is same 
 *       for images of different size because Yolo takes in a (416, 416) image.      
 */
TEST(networkOutputCheck, testOutputLayerSize) {
    // Sanity check for getting same output size
    // for different iinput size
    ImageInference infer;
    IOModule ioHandler;

    Mat image1 = ioHandler.readImage("../data/testImage1.jpg", false);
    Mat image2 = ioHandler.readImage("../data/testImage2.jpg", false);

    infer.setModelParams();
    vector<Mat> networkOutput1= infer.runForwardPass(image1);
    vector<Mat> networkOutput2 = infer.runForwardPass(image2);
    
    ASSERT_NE(image1.size(), image2.size());
    ASSERT_EQ(networkOutput1.size(), networkOutput2.size());
}

/**
 *@brief Test for inference module. 
 *       Tests that the number of bounding boxes returned are same as the 
 *       ground truth.      
 */
TEST(fullInferenceCheck, testLabelOutput) {
    ImageInference infer;
    IOModule iomodule;
    Mat image = iomodule.readImage("../data/testImage.jpg", false);
    infer.setModelParams();
    vector<Mat> finalLayerOut = infer.runForwardPass(image);
    infer.applyNMS(image, finalLayerOut);
    auto output = infer.getBoxes();
    uint8_t reqOutput = 1;
    ASSERT_EQ(output.size(), reqOutput);
}