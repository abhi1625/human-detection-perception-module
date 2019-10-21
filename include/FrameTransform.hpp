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

#include "IOModule.hpp"

class FrameTransform {
public:
    /**
     * @brief default constructor
     */
    FrameTransform();

    /**
     * @brief endToBase converts coordinates of the detected objects from sensor
     *        end to robot's base frame.
     * @param imgPoints - const reference to matrix of detected coordinates
     * @return Matrix containing coordinates in robot's base frame
     */ 
    cv::Mat endToBase(const Mat &imgPoints);

    /**
     * @brief baseToEnd converts coordinates of the detected objects from robot's
     *        base frame to sensor frame.
     * @param coords - const reference to image matrix containing detection
     *                 coordinates in robot's base frame
     * @return Matrix containing coordinates in sensor frame
     */ 
    cv::Mat baseToEnd(const Mat &coords);

    /**
     * @brief default destructor
     */
    ~FrameTransform();

private:
    cv::Mat coords;       // Matrix containing coordinates in robot's base frame
    cv::Mat imgPoints;    // Matrix containing coordinates in sensor frame
};

