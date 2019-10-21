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

/**@file IOModuleTest.cpp
 * @brief Test source file for input-output module.
 *        Contains the tests for the defined methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi, Kartik Madhira
 * @created on : Oct 20, 2019
 */

#include <gtest/gtest.h>
#include "../include/IOModule.hpp"

/**
 *@brief Test for read methods. 
 *       Tests if the functions taking user inputs read data as required. 
 */
TEST(checkInputRead, testInputRead) {
    std::istringstream inputType("2");
    std::istringstream inputDir("../data/"); 
    std::istringstream outputDir("../data/");
    std::istringstream setID("0");

    IOModule ioHandler;
    ioHandler.readInputType(inputType);    
    ioHandler.readInputDir(inputDir);
    ioHandler.readOutputDir(outputDir);
    ioHandler.setCameraID(setID);
    ASSERT_EQ(ioHandler.returnInputType(), 2);
    ASSERT_EQ(ioHandler.returnInputDir(), "../data/");
    ASSERT_EQ(ioHandler.returnOutputDir(), "../data/");
    ASSERT_EQ(ioHandler.returnCameraID(), 0);
}

/**
 *@brief Test for getInputPath method.
 *       Tests if the method reads expected number of image files in a given
 *       directory.
 */
TEST(checkInputDirectory, testInputFiles) {
    IOModule ioHandler;
    vector<string> filesVector = ioHandler.getInputPath("../app");
    uint8_t checkValue = 7;
    ASSERT_EQ(filesVector.size(), checkValue);
}

/**
 *@brief Test for readImage method. 
 *       Tests that the method reads the image correctly.      
 */
TEST(checkInputImage, testReadImage) {
    IOModule ioHandler;
    Mat handlerImage = ioHandler.readImage("../data/testImage.jpg", false);
    ASSERT_EQ(handlerImage.size().height, 350);
    ASSERT_EQ(handlerImage.size().width, 590);
}

/**
 *@brief Test for saveTextFile method. 
 *       Tests that the text file written by the method contains data in the
 *       required format.      
 */
TEST(checkSavedFile, testSavedFile) {
    IOModule ioHandler;
    vector<vector<float>> coordinates {{2.0, 4.0, 4.0, 3.0, 8.0}};
    vector<string> labels {"person"};
    std::istringstream outputDir("../data");
    vector<int> imageList {1};
    ioHandler.readOutputDir(outputDir);
    ioHandler.saveTextFile(coordinates, labels, imageList);
    string line;
    std::ifstream savedFile("../data/finalOutput.txt");
    std::getline(savedFile, line);
    std::getline(savedFile, line);
    std::istringstream buf(line);
    std::istream_iterator<string> beg(buf), end;
    vector<string> values(beg, end);

    ASSERT_EQ(values[0], "1");
    ASSERT_EQ(values[1], "1");
    ASSERT_EQ(values[2], "person");
    ASSERT_EQ(values[3], "2");
    ASSERT_EQ(values[4], "4");
    ASSERT_EQ(values[5], "4");
    ASSERT_EQ(values[6], "3");
    ASSERT_EQ(values[7], "8");
    std::remove("../data/finalOutput.txt");
}