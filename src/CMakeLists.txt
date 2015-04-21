# src/CMakeLists.txt

add_executable(
	FaceFramboise

	main.cpp
	detection.hpp
	detection.cpp
	recognition.hpp
	recognition.cpp
	Histogram.hpp
	Histogram.cpp
	Person.hpp
	Person.cpp
	Gallery.hpp
	Gallery.cpp
)

target_link_libraries(
	FaceFramboise

	libboost_serialization.so
	libsqlite3.so
	${OpenCV_LIBS}
)

