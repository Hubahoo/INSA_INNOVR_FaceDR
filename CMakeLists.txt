cmake_minimum_required(VERSION 2.8)

project(FaceFramboise)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

#find_package( OpenCV REQUIRED )

include_directories(
	/usr/include/
	/usr/local/include/
)

link_directories(
	/usr/local/lib/
)

add_executable(
	FaceRecognition

	main.cpp
	init.hpp
	init.cpp
	detection.hpp
	detection.cpp
	FaceRecognition.cpp
	Histogram.hpp
	Histogram.cpp
	Gallery.hpp
	Gallery.cpp
	Person.hpp
	Person.cpp
)


target_link_libraries(
	FaceRecognition

	libboost_serialization.so
	libsqlite3.so
	
	libopencv_core.so
	libopencv_highgui.so
	libopencv_imgproc.so
	libopencv_objdetect.so
	libopencv_imgcodecs.so
)

#target_link_libraries( FaceFramboise ${OpenCV_LIBS} )



