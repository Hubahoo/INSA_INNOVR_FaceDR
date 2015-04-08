cmake_minimum_required(VERSION 2.8)
project( FaceFramboise )
find_package( OpenCV REQUIRED )
add_executable( FaceFramboise main.cpp init.hpp init.cpp detection.hpp 
detection.cpp)
target_link_libraries( FaceFramboise ${OpenCV_LIBS} )
