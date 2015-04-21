# src/CMakeLists.txt

add_executable(
	FaceFramboise

	main.cpp
	init.hpp
	init.cpp
	#detection.hpp
	#detection.cpp
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

