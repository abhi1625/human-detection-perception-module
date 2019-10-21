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

/**@file IOModule.cpp
 * @brief Source file for IOModule to handle input and output interface for the
 *        whole pipeline. Contains declarations for required headers and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 21, 2019
 */

#include "../include/IOModule.hpp"

IOModule::IOModule() {

}

void IOModule::readInputType(std::istream& input) {
    // 1. Get the type of the input feed
    // 2. set the input and output directories
    cout << "Welcome to the Acme Robotics Perception App!\n";
    cout << "Enter type of input feed\n" 
         << "Key 1 - Image\n" 
         << "Key 2 - Video\n"
         << "Key 3 - Live camera\n" 
         << "Key 4 - Run Demo\n" << std::flush;
    // Loop in until proper digit is entered
    input >> inputType;
    // Check if input is valid
    if (inputType == 3) {
        IOModule::setCameraID(cin);
    }
    input.clear();
}

void IOModule::readInputDir(std::istream& input) {
    cout << "Enter the desired Input directory\n" << std::flush;
    input >> inputDirectory;
    input.clear();
}

void IOModule::readOutputDir(std::istream& input) {
    cout << "Enter the desired Output directory\n" << std::flush;
    input >> outputDirectory;
    input.clear();
}

void IOModule::setCameraID(std::istream& input) {
    
    cout << "Enter the camera ID of the camera you want to use:" << std::flush;
    input >> cameraID;
    input.clear();
}

string IOModule::returnInputDir() {
    string _inputDir = inputDirectory;
    return _inputDir;
}

string IOModule::returnOutputDir() {
    string _outputDir = outputDirectory;
    return _outputDir;
}


Mat IOModule::readImage(string path, bool showImage) {
    Mat image;
    image = cv::imread(path);
    if (!image.data) {
        cout << "Could not read image" << endl;
    }
    if (showImage) {
        cv::namedWindow("Debug display", CV_WINDOW_AUTOSIZE);
        cv::imshow("Debug display", image);
        cv::waitKey(0);
    }
    return image;
}

vector<string> IOModule::getInputPath(string imagesPath) {
    vector<string> pathString;
    path p{imagesPath};
    directory_iterator it(p);
    // https://theboostcpplibraries.com/boost.filesystem-iterators
    while (it != directory_iterator{}) {
        pathString.emplace_back(it->path().string());
        it++;
    }
    return pathString;
}

int IOModule::returnCameraID() {
    int _camID = cameraID;
    return _camID;
}

int IOModule::returnInputType() {
    int _inputType = inputType;
    return _inputType;
}

void IOModule::saveTextFile(vector<vector<float>> boxCoords, 
                            vector<std::string> labels,
                            vector<int> imageList) {
    outFile.open(outputDirectory + "/finalOutput.txt");
    // Iterate over each of the box coordinates
    outFile << "FrameID\t" << "ID\t" << "Label\t" << "x\t" << "y\t" << "z\t" << "w\t" << "h\n";  
    int i = 0;
    for (auto& eachBox : boxCoords) {
        outFile << imageList[i] << "\t" << i+1 << "\t" << labels[i] << "\t";
        for (auto& eachCord : eachBox) {
            outFile << eachCord << "\t";
        }
        outFile << "\n";
        ++i;
    }

    outFile.close();
}

void IOModule::drawBoundingBoxes(Mat& image, int boxLeft,
                                int boxTop, int boxRight, int boxBottom) {
    cv::rectangle(image, cv::Point(boxLeft, boxTop), 
                  cv::Point(boxRight, boxBottom), 
                  cv::Scalar(0, 178, 0), 3);
    }

void IOModule::setDefaultInputs() {
    inputDirectory = "../data/demoImages";
    outputDirectory = "../data/output";
}