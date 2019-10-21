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

/**@file PerceptionModuleTest.cpp
 * @brief Test source file for perception module.
 *        Contains the tests for the defined methods.
 *
 * Detailed description follows here.
 * @author     : Abhinav Modi
 * @created on : Oct 21, 2019
 */

#include <gtest/gtest.h>
#include "../include/PerceptionModule.hpp"

/**
 *@brief Test for runDetection method. 
 *       Tests the if the output of the method on successful 
 *       execution as expected. 
 */

TEST(checkPerceptionRun, testDetectPipeline) {
    PerceptionModule detect;
    ASSERT_EQ(detect.runDetection(false, true), 0);
}

/**
 *@brief Test for runDetection method. 
 *       Tests the if the output of the method on successful 
 *       execution as expected. 
 */
TEST(checkPerceptionRunVid, testDetectPipelineVid) {
    PerceptionModule detect;
    ASSERT_EQ(detect.runDetection(true, false), 0);
}