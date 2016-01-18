project(Projekt)

find_package(OpenCV    3.0.0    REQUIRED)
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set( sources
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
QT5_WRAP_CPP(Cmake_hdr_moc mainwindow.h)
QT5_WRAP_UI(Cmake_form_hdr mainwindow.ui)

add_library(mainwindow ${Cmake_hdr_moc} ${Cmake_form_hdr})
qt5_use_modules(mainwindow Widgets)

add_executable(Projekt main.cpp mainwindow
	${sources}
	${headers} 
)
qt5_use_modules(Projekt Core Gui Widgets) 
target_link_libraries(Projekt
     ${OpenCV_LIBS}
)
include_directories(
     ${OpenCV_INCLUDE_DIRS}
)

