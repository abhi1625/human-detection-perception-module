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
#pragma once

#include <string>
#include <vector>
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
    void applyNMS(const Mat& inferImage, const vector<Mat>& finalLayer);

    /**
     * @brief feedOutputNames returns the names of all the classes for which YoloV3
     *        is trained.
     * @param net - const reference to an openCV object of the Yolo CNN model
     * @return vector containing names of all classes in the output layer of Yolo
     */ 
    vector<cv::String> feedOutputNames(const cv::dnn::Net& net);

    /**
     * @brief getLabels provides access to the private member labels
     * @param None
     * @return vector of labels given by YoloV3
     */ 
    vector<int> getLabels();

    /**
     * @brief getLabelConfidence provides access to the private member
     *        labelConfidences
     * @param None
     * @return vector of confidence scores for each corresponding label
     */ 
    vector<float> getLabelConfidence();

    /**
     * @brief getLabelConfidence provides access to the private member
     *        boxCords
     * @param None
     * @return vector containing information of bounding boxes detected
     */ 
    vector<cv::Rect> getBoxes();

    /**
     * @brief default destructor
     */
    ~ImageInference();

 private:
    int imageSize;                      // dimension of a square image

    /**
     * @brief threshold to identify a network output as a detection
     */
    float confidenceThresh;

    /**
     * @brief threshold for confidence score to suppress weak detections
     */
    float nmsThresh;


    /**
     * @brief path to a trained model weights file
     */
    string modelWeightFile;

    /**
     * @brief openCV object of the Yolo CNN model
     */
    cv::dnn::Net network;

    /**
     * @brief vector of labels given by YoloV3
     */
    vector<int> labels;

    /**
     * @brief path of trained model configuration file
     */
    string modelConfigFile;

    /**
     * @brief vector of classes for which Yolo is trained
     */
    vector<string> classes;

    /**
     * @brief output vector of confidence scores of each label
     */
    vector<float> labelConfidences;

    /**
     * @brief vector containing bounding box information
     */
    vector<cv::Rect> boxCords;
};

