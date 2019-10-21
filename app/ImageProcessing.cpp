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

/**@file ImageProcessing.cpp
 * @brief Source file for ImageProcessing to perform basic operations on images.
 *        Contains declarations for required headers and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 21, 2019
 */

#include "../include/ImageProcessing.hpp"

ImageProcessing::ImageProcessing() {

}

Mat ImageProcessing::resizeImage(int h, int w, const Mat &image) {
    Mat _resizedImage;
    cv::resize(image, _resizedImage, cv::Size(w, h), 0, 0, cv::INTER_LINEAR);
    return _resizedImage;
}

Mat ImageProcessing::medianBlur(const Mat &image) {
    Mat _blurredImage;
    cv::medianBlur(image, _blurredImage, 3);
    return _blurredImage;
}

Mat ImageProcessing::gaussianBlur(const Mat &image) {
    Mat _blurredImage;
    cv::GaussianBlur(image, _blurredImage, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
    return _blurredImage;
}

ImageProcessing::~ImageProcessing() {

}
