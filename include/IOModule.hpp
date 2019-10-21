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

/**@file IOMudule.hpp
 * @brief Header file for input-output module.
 *        Contains declarations for required headers and methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 19, 2019
 */

#pragma once

#include <glob.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>

using std::string;
using std::cout;
using std::cin;
using std::vector;
using cv::Mat;
using std::endl;

using namespace boost::filesystem; //NOLINT

class IOModule {
public:
    /**
     * @brief default constructor
     */
    IOModule();
    
    /**
     * @brief readInput gets the input format from the user i.e., images - 1, 
     *        2 - video input, 3 - live camera feed  
     * @param input - reference to an input stream object to read user input  
     * @return None
     */
    void readInputType(std::istream& input);

    /**
     * @brief readInputDir gets and stores the input directory from the user  
     * @param input - reference to an input stream object to read user input  
     * @return None
     */
    void readInputDir(std::istream& input);

    /**
     * @brief readOutputDir gets and stores the output directory from the user  
     * @param input - reference to an input stream object to read user input  
     * @return None
     */
    void readOutputDir(std::istream& input);

    /**
     * @brief setCameraID sets the Camera device ID as given by the user
     * @param input - reference to an input stream object to read user input 
     * @return None
     */
    void setCameraID(std::istream& input);

    /**
     * @brief returnInputDir provides access to private member input directory  
     * @param None
     * @return path of input directory
     */
    string returnInputDir();

    /**
     * @brief returnOutputDir provides access to private member output directory  
     * @param None
     * @return path of output directory
     */
    string returnOutputDir();

    /**
     * @brief getInputPath returns a vector of paths to images 
     *                     present in a given directory.  
     * @param imagesPath - path of the directory containing images
     * @return vector containing paths to each image.
     */    
    vector<string> getInputPath(string imagesPath);

    /**
     * @brief readimage reads and displays image from a given path 
     * @param path - path of an image file
     * @return image matrix in openCV format
     */    
    Mat readImage(string path, bool show_image = false);

    /**
     * @brief returnInputType provides access to private variable inputType 
     * @param None
     * @return input type: images - 1, video - 2, camera feed - 3
     */    
    int returnInputType();

    /**
     * @brief returnCameraID provides acces to private member camera ID 
     * @param None
     * @return camera device ID
     */    
    int returnCameraID();

    /**
     * @brief drawBoundingBoxes draws bounding boxes around detected objects in
     *        an input image frame 
     * @param image - image matrix on which boundign box is drawn
     * @param boxLeft - left-most coordinate of the bounding box
     * @param boxTop - top-most coordinate of the bounding box
     * @param boxRight - right-most coordinate of the bounding box
     * @param boxBottom - bottom-most coordinate of the bounding box
     * @return None 
     */ 
    void drawBoundingBoxes(Mat &image, int boxLeft,
                          int boxTop, int boxRight, int boxBottom);

    /**
     * @brief saveTextFile writes detection output in a text file which contains
     *                     coordinates and dimensions of the bounding box and 
     *                     its corresponding label. 
     * @param boxCoords - vector of vector containing
     *                    bounding box coordinates and dimensions
     * @param labels - vector of labels corresponding to each bounding box
     * @param imageList - vector containing list of images to assign frame ID to
     *                    bounding boxes
     * @return None 
     */ 
    void saveTextFile(vector<vector<float>> boxCoords, vector<string> labels,
                     vector<int> imageList);

    /**
     * @brief setDefaultInputs sets a default input and output directory for
     *        the module
     */    
    void setDefaultInputs();
    
    /**
     * @brief default destructor
     */    
    ~IOModule();

private:
    string inputDirectory;      // path to directory containing input images/vides
    int inputType;              // id assigned to input type: images - 1, video - 2, camera-feed - 3
    string outputDirectory;     // path to directory in which text file will be saved
    int cameraID;               // device ID of the camera from which data is to be read
    std::ofstream outFile;      // output stream object to save output text file.
};