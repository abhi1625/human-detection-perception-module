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

/**@file ImageInference.hpp
 * @brief Header file for image-inference module to run the forward pass for
 *        object detection. Contains declarations for required headers 
 *        and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 20, 2019
 */

#include "IOModule.hpp"

class ImageInference {
public:
    /**
     * @brief default constructor
     */
    ImageInference();

    /**
     * @brief setModelParams loads and sets the parameters of the CNN - YoloV3
     *        and other thresholding parameters required for the forward pass.          
     * @param None
     * @return None 
     */ 
    void setModelParams();

    /**
     * @brief runForwardPass takes an input image and runs it through the Yolo
     *        network for object detection and returns output of the final layer
     *        of the CNN.
     * @param inferImage - const reference of image on which inference is run  
     * @return vector containing information of all the predicted bounding boxes
     *         in the final layer of the network
     */ 
    vector<Mat> runForwardPass(const Mat &inferImage);

    /**
     * @brief applyNMS suppresses the predictions below a given threshold 
     *        to only return detections with good confidence score.
     * @param inferImage - const reference of image on which inference is run
     * @param finalLayer - vector containing information of all the predicted 
     *                      bounding boxes in the final layer of the network.
     * @return None
     */ 
    void applyNMS(Mat& inferIMage, const vector<Mat>& finalLayer);

    /**
     * @brief default destructor
     */
    ~ImageInference();

private:
     float confidenceThresh;   // threshold to identify a network output as a detection 
     float nmsThresh;          // threshold for confidence score to suppress weak detections 
     int imageSize;            // dimension of a square image
     string modelConfigFile;   // path to a trained model configuration file
     string modelWeightFile;   // path to a trained model weights file
     cv::dnn::Net network;     // openCV object of the Yolo CNN model
};

