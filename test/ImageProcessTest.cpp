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

/**@file ImageProcessTest.cpp
 * @brief Test source file for the Image processing module.
 *        Contains the tests for the defined methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi, Kartik Madhira
 * @created on : Oct 20, 2019
 */

#include <gtest/gtest.h>
#include "../include/ImageProcessing.hpp"

/**
 *@brief Test for gaussianBlur image processing method. 
 *       Tests if the method throws any exceptions. 
 */
TEST(checkGaussianBlur, testGaussianBlur) {
    IOModule ioHandler;
    ImageProcessing processImage;
    Mat handlerImage = ioHandler.readImage("../data/testImage.jpg", false);
    Mat outputImage = processImage.gaussianBlur(handlerImage);
    ASSERT_EQ(outputImage.size().height, 350);
    ASSERT_EQ(outputImage.size().width, 590);
}

/**
 *@brief Test for medianBlur image processing method. 
 *       Tests if the method throws any exceptions. 
 */
TEST(checkMedianBlur, testMedianBlur) {
    IOModule ioHandler;
    ImageProcessing processImage;
    Mat handlerImage = ioHandler.readImage("../data/testImage.jpg", false);
    Mat outputImage = processImage.medianBlur(handlerImage);
    ASSERT_EQ(outputImage.size().height, 350);
    ASSERT_EQ(outputImage.size().width, 590);
}

/**
 *@brief Test for resizeImage image processing method. 
 *       Tests if the method throws any exceptions. 
 */
TEST(checkResizeOperation, testResizingImage) {
    IOModule ioHandler;
    ImageProcessing processImage;
    Mat handlerImage = ioHandler.readImage("../data/testImage.jpg", false);
    Mat outputImage = processImage.resizeImage(212,212, handlerImage);
    ASSERT_EQ(outputImage.size().height, 212);
    ASSERT_EQ(outputImage.size().width, 212);
}
