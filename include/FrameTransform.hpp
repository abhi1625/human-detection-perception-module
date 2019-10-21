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
 * @brief Header file for frame-transform module to convert detection outputs
 *        to useful information in the robot's reference frame. Contains 
 *        declarations for required headers and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 20, 2019
 */
#pragma once

#include "IOModule.hpp"

class FrameTransform {
public:
    /**
     * @brief default constructor
     */
    FrameTransform();

    /**
     * @brief endToBase converts coordinates of the detected objects from 2D image
     *        frame to 3D camera frame
     * @param Boxes - const reference to vector containing bounding box information
     * @return None
     */ 
    void imageToCamera(const vector<cv::Rect> &Boxes);

    /**
     * @brief baseToEnd converts coordinates of the detected objects from camera
     *        frame to robot's base frame
     * @param None
     * @return None
     */ 
    void cameraToBase();

    /**
     * @brief provides access to private member coords3D
     * @param None
     * @return matrix containing 3D coordinates of the detections in robot's 
     *         base frame
     */ 
    cv::Mat getCoords3D();

    /**
     * @brief provides access to private member coordsCam
     * @param None
     * @return matrix containing 3D coordinates of the detections in camera 
     *         coordinate frame
     */ 
    cv::Mat getCoordsCam();

    /**
     * @brief returns 3D coordinates in desired format to save in text file 
     * @param Boxes - const refernce to detected bounding boxes in the image 
     * @return vector containing 3D coordinates and bounding box dimensions
     *         in robot's base frame for each detection
     */ 
    vector<vector<float>> outputCoords(const vector<cv::Rect> &Boxes);

    /**
     * @brief default destructor
     */
    ~FrameTransform();

private:
    /**
     * @brief Matrix containing coordinates in robot's base frame
     */
    cv::Mat coords3D;
    
    /**
     * @brief Matrix containing coordinates in camera frame
     */
    cv::Mat coordsCam = cv::Mat::ones(1,3, CV_64F);
};

