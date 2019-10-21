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
     * @brief resizeImage resizes input image to desired dimensions
     * @param h - desired height of the image in pixels
     * @param w - desired width of the image in pixels
     * @param image - const reference to the image matrix to be resized
     * @return resized image matrix in openCV format
     */ 
    Mat resizeImage(int h, int w, const Mat &image);

    /**
     * @brief medianBlur performs median blurring operation on an input image.
     * @param image - const reference to the image matrix to be blurred
     * @return blurred image matrix in openCV format
     */ 
    Mat medianBlur(const Mat &image);

    /**
     * @brief gaussianBlur performs gaussian blur operation on an input image
     * @param image - const reference to the image matrix to be blurred
     * @return blurred image matrix in openCV format
     */ 
    Mat gaussianBlur(const Mat &image);

    /**
     * @brief default destructor
     */ 
    ~ImageProcessing();
};

