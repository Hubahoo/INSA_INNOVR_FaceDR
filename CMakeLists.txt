cmake_minimum_required(VERSION 2.8)

project(FaceFramboise)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)


include_directories(
	/usr/include/
	/usr/local/include/
)

link_directories(
	/usr/local/lib/
)

add_executable(
	FaceFramboise

	main.cpp
#	init.hpp
#	init.cpp
#	detection.hpp
#	detection.cpp
	FaceRecognition.cpp
	Histogram.hpp
	Histogram.cpp
	Gallery.hpp
	Gallery.cpp
	Person.hpp
	Person.cpp
)

target_link_libraries(
	FaceFramboise

	libboost_serialization.so
	libsqlite3.so
	${OpenCV_LIBS}
)

