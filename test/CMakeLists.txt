set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    DetectionTest.cpp
    IOModuleTest.cpp
    ImageProcessTest.cpp
    ../app/ImageInference.cpp
    ../app/ImageProcessing.cpp
    ../app/IOModule.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include
                                           ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cpp-test PUBLIC gtest PUBLIC ${OpenCV_LIBS} ${Boost_LIBRARIES})
