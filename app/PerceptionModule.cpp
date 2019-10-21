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

#include "../include/PerceptionModule.hpp"

PerceptionModule::PerceptionModule() {

}

int PerceptionModule::runDetection(bool test) {
    // Gather all the modules
    ImageInference inferModule;
    ImageProcessing imageProcessModule;
    IOModule ioModule;
    FrameTransform frameTransModule;
    // Read User inputs
    if (test) {
        std::istringstream inputType("4");
        ioModule.readInputType(inputType);
    } else {
        ioModule.readInputType(cin);
    }
    if (ioModule.returnInputType() < 4) {
        if (ioModule.returnInputType() == 3) {
            std::istringstream inputDir("../data/");
            ioModule.readOutputDir(cin);
        } else {
            ioModule.readInputDir(cin);
            ioModule.readOutputDir(cin);
        }
    }
    // Initialize YOLOv3 network
    inferModule.setModelParams();

    string savedPath = ioModule.returnInputDir();
    if (ioModule.returnInputType() == 1) {
        // Get the vector of path of each image
        vector<string> pathList = ioModule.getInputPath(savedPath);
        // Read every image and forward pass through inference
        vector<cv::Rect> boxesList;
        vector<string> labelList;
        vector<int> imageList;
        int imageCounter = 0;

        for (auto &imagePath : pathList) {
            Mat image = ioModule.readImage(imagePath, false);
            
            Mat tempImage = imageProcessModule.gaussianBlur(image);
            tempImage = imageProcessModule.medianBlur(tempImage);
            
            vector<Mat> finalLayerOut = inferModule.runForwardPass(tempImage);
            inferModule.applyNMS(tempImage, finalLayerOut);
            auto boxCords = inferModule.getBoxes();
            vector<int> labels = inferModule.getLabels();
            if (boxCords.size() > 0) {
                for (size_t i = 0; i <= boxCords.size(); ++i) {
                    cv::Rect bBox = boxCords[i];
                    boxesList.push_back(bBox);
                    labelList.push_back("person");
                    imageList.push_back(imageCounter);
                    ioModule.drawBoundingBoxes(image, bBox.x, bBox.y, 
                                                bBox.x + bBox.width, bBox.y + bBox.height);
                }
                if (!test) {
                    cv::namedWindow("AcmeViz", CV_WINDOW_AUTOSIZE);
                    cv::imshow("AcmeViz", image);
                    cv::waitKey(0);
                }
            } else {
                cout << "No bounding boxes found!\n";
            }
            imageCounter++;
        }
        
        // Saving files
        frameTransModule.imageToCamera(boxesList);
        frameTransModule.cameraToBase();
        auto boxCoords = frameTransModule.outputCoords(boxesList);
        ioModule.saveTextFile(boxCoords, labelList, imageList);
        cout << "Thank you for using the module!\n";
        return 0;
    }

    if (ioModule.returnInputType() == 4) {
        ioModule.setDefaultInputs();
        savedPath = ioModule.returnInputDir();
        // Get the vector of path of each image
        vector<string> pathList = ioModule.getInputPath(savedPath);
        // Read every image and forward pass through inference
        vector<cv::Rect> boxesList;
        vector<string> labelList;
        vector<int> imageList;
        int imageCounter = 0;

        for (auto &imagePath : pathList) {

            Mat image = ioModule.readImage(imagePath, false);
            
            Mat tempImage = imageProcessModule.gaussianBlur(image);
            tempImage = imageProcessModule.medianBlur(tempImage);
            
            vector<Mat> finalLayerOut = inferModule.runForwardPass(tempImage);
            inferModule.applyNMS(tempImage, finalLayerOut);
            auto boxCords = inferModule.getBoxes();
            vector<int> labels = inferModule.getLabels();
            if (boxCords.size() > 0) {
                for (size_t i = 0; i <= boxCords.size(); ++i) {
                    cv::Rect bBox = boxCords[i];
                    boxesList.push_back(bBox);
                    labelList.push_back("person");
                    imageList.push_back(imageCounter);
                    ioModule.drawBoundingBoxes(image, bBox.x, bBox.y, 
                                                bBox.x + bBox.width, bBox.y + bBox.height);
                }
                if (!test) {
                    cv::namedWindow("AcmeViz", CV_WINDOW_AUTOSIZE);
                    cv::imshow("AcmeViz", image);
                    cv::waitKey(0);
                }
            } else {
                cout << "No bounding boxes found!\n";
            }
            imageCounter++;
        }
        
        // Saving files
        frameTransModule.imageToCamera(boxesList);
        frameTransModule.cameraToBase();
        auto boxCoords = frameTransModule.outputCoords(boxesList);
        ioModule.saveTextFile(boxCoords, labelList, imageList);
        cout << "Thank you for using the module!\n";
        return 0;
    }

    if (ioModule.returnInputType() == 2) {
        capture = cv::VideoCapture(ioModule.returnInputDir());
    }
    
    if (ioModule.returnInputType() == 3) {
        capture = cv::VideoCapture(ioModule.returnCameraID());
    }
    
    if (!capture.isOpened()) {
        std::cout << "Error opening video stream or file!" << std::endl;
        return -1;
    }
    vector<cv::Rect> boxesList;
    vector<string> labelList;
    vector<int> imageList;
    int imageCounter = 0;
    while (capture.read(frame)) {
        if (frame.empty()) {
            break;
        }
        Mat tempImage = imageProcessModule.gaussianBlur(frame);
        tempImage = imageProcessModule.medianBlur(tempImage);
        
        vector<Mat> finalLayerOut = inferModule.runForwardPass(tempImage);
        inferModule.applyNMS(tempImage, finalLayerOut);
        auto boxCords = inferModule.getBoxes();
        vector<int> labels = inferModule.getLabels();
        if (boxCords.size() > 0) {
            for (size_t i = 0; i <= boxCords.size(); ++i) {
                cv::Rect bBox = boxCords[i];
                boxesList.push_back(bBox);
                labelList.push_back("person");
                imageList.push_back(imageCounter);
                ioModule.drawBoundingBoxes(tempImage, bBox.x, bBox.y, 
                                            bBox.x + bBox.width, bBox.y + bBox.height);
            }
            if (!test) {
                cv::namedWindow("AcmeViz", CV_WINDOW_AUTOSIZE);
                cv::imshow("AcmeViz", tempImage);
                char c = static_cast<char>(cv::waitKey(5));
                if (c == 27) {
                    break;
                }            
            }
        } else {
            cout << "No bounding boxes found!\n";
        }
        imageCounter++;
        frame = 0;
    }
    // Saving files
    frameTransModule.imageToCamera(boxesList);
    frameTransModule.cameraToBase();
    auto boxCoords = frameTransModule.outputCoords(boxesList);
    ioModule.saveTextFile(boxCoords, labelList, imageList);
    cout << "Thank you for using the module!\n";
    return 0;
    

}

PerceptionModule::~PerceptionModule() {

}