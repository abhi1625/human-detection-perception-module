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

/**@file ImageInference.cpp
 * @brief Source file for ImageInference module. Handles forward pass of an
 *        image frame through YoloV3 CNN for human detection. Contains 
 *        declarations for required headers and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 21, 2019
 */

#include "../include/ImageInference.hpp"

ImageInference::ImageInference() {

}

void ImageInference::setModelParams() {
    // Set all the model parameters and model load
    modelConfigFile = "../data/yolov3.cfg";
    modelWeightFile = "../data/yolov3.weights";
    // Load the network
    network = cv::dnn::readNetFromDarknet(modelConfigFile, modelWeightFile);
    network.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    network.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    // Load all the classes from COCO dataset
    string classDict = "../data/coco.names";
    std::ifstream ifs(classDict.c_str());
    string line;
    while (getline(ifs, line)) {
        classes.push_back(line);
    }
    // Set parameters
    confidenceThresh = 0.9;
    nmsThresh = 0.85;  // Non-maximum suppression threshold
    imageSize = 416;  // Set image size w.r.t yolo network input

}

vector<Mat> ImageInference::runForwardPass(const Mat &inferImage) {
    // Run a forward inference on the yolo network
    Mat blob;
    cv::dnn::blobFromImage(inferImage, blob, 1/255.0, 
                           cv::Size(imageSize, imageSize), 
                           cv::Scalar(0,0,0), true, false);
    network.setInput(blob);

    // Initialize an output layer of vectors
    vector<Mat> finalLayer;
    // Run the forward pass at once to the final layer
    network.forward(finalLayer, feedOutputNames(network));

    return finalLayer;
}

vector<cv::String> ImageInference::feedOutputNames(const cv::dnn::Net& net) {
    static vector<cv::String> outputLayerStrings;
    if (outputLayerStrings.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        vector<int> outLayers = net.getUnconnectedOutLayers();
        
        //get the names of all the layers in the network
        vector<cv::String> layersNames = net.getLayerNames();
        
        // Get the names of the output layers in names
        outputLayerStrings.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        outputLayerStrings[i] = layersNames[outLayers[i] - 1];
    }
    return outputLayerStrings;
}

void ImageInference::applyNMS(Mat& inferImage, const vector<Mat>& finalLayer) {
    // Stich the final layer outputs for bounding box
    // coordinates and gather the labels. Finally apply 
    // Non-Maximal Supression(NMS) to suppress boxes with 
    // low confidences.
    for (size_t i = 0; i < finalLayer.size(); ++i) {  
        float* data = (float*)finalLayer[i].data;
        for (int j = 0;j < finalLayer[i].rows; ++j, data += finalLayer[i].cols)
        {
            Mat scores = finalLayer[i].row(j).colRange(5, finalLayer[i].cols);
            cv::Point labelLocations;
            double confidences;
            // Get the value and location of the maximum score
            cv::minMaxLoc(scores, 0, &confidences, 0, &labelLocations);
            if (confidences > confidenceThresh)
            {
                int centerX = (int)(data[0] * inferImage.cols);
                int centerY = (int)(data[1] * inferImage.rows);
                int width = (int)(data[2] * inferImage.cols);
                int height = (int)(data[3] * inferImage.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                
                if (labelLocations.x == 0) {
                    labels.push_back(labelLocations.x);
                    labelConfidences.push_back((float)confidences);
                    boxCords.push_back(cv::Rect(left, top, width, height));
                }
            }
        }
    }
    
    // perform non-maximal suppression
    vector<int> indices;
    cv::dnn::NMSBoxes(boxCords, labelConfidences, 
                      confidenceThresh, nmsThresh, indices);
}

vector<int> ImageInference::getLabels() {
    vector<int> _labels = labels;
    return _labels;
}

vector<float> ImageInference::getLabelConfidence() {
    vector<float> _confidences = labelConfidences;
    return _confidences;
}

vector<cv::Rect> ImageInference::getBoxes() {
    vector<cv::Rect> _coordinates = boxCords;
    return _coordinates;
}