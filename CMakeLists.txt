project(Projekt)

find_package(OpenCV    3.0.0    REQUIRED)

include_directories(
     ${OpenCV_INCLUDE_DIRS}
)
set( sources
	main.cpp
	Encryption.cpp
	ImageProcessing.cpp
	FaceRecognition.cpp
	Binary.cpp
	Camera.cpp
)
set( headers
	Encryption.hpp
	ImageProcessing.hpp
	FaceRecognition.hpp
	Binary.hpp
	Camera.hpp
)	
add_executable(Projekt
	${sources}
	${headers}     
)

target_link_libraries(Projekt
     ${OpenCV_LIBS}
)