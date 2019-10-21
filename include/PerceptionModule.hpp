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

/**@file PerceptionModule.hpp
 * @brief Header file for perception module which is a wrapper for all other 
 *        modules. Contains declarations for required headers and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 20, 2019
 */
#pragma once

#include "IOModule.hpp"
#include "ImageProcessing.hpp"
#include "ImageInference.hpp"

class PerceptionModule {

public:
    /**
     * @brief default constructor
     */
    PerceptionModule();

    /**
     * @brief runDetection is the wrapper function to run the object detection
     *        pipeline.
     * @param interface - an object of input-output module to read input and
     *                    write the output.
     * @param test - bool to check if the function is being called in test
     * @return 0 if function runs successfully and -1 otherwise.
     */ 
    int runDetection(IOModule interface, bool test);

    /**
     * @brief default destructor
     */
    ~PerceptionModule();

private:

    /**
     * @brief data structure to store image frames
     */
    cv::Mat frame;

    /**
     * @brief object for video and camera-feed input
     */
    cv::VideoCapture cap;

    /**
     * @brief vector to store bounding box coordinates, dimensions and
     *        corresponding labels of detected objects
     */
    vector<vector<float>> detectedObjects;
};

