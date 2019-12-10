cmake_minimum_required(VERSION 3.0)

project(projectSI)


#_______________________________________________________________find libraries

find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
	message(STATUS "SDL2 found")
endif()

find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
	message(STATUS "OpenGL found")
endif()

find_package(GLEW REQUIRED)
if(${GLEW_FOUND})
	message(STATUS "GLEW found")
endif()

find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
else()
    include_directories("/usr/include/eigen3") # manually specify the include location
endif()


#_______________________________________________________________Include directories

include_directories(${SDL2_INCLUDE_DIRS} 
			${OPENGL_INCLUDE_DIR} 
			${GLEW_INCLUDE_DIRS} 
			${EIGEN3_INCLUDE_DIR} 
			glimac/include 
			third-party/include
			third-party/include/ImGUI
			third-party/include/glad/include
		#	${CMAKE_SOURCE_DIR}third-party/
			)


set(ALL_LIBRARIES glimac ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${EIGEN3_LIBRARIES})


#_______________________________________________________________sets
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
file(GLOB MAIN_CODE "code")
file(GLOB_RECURSE IMGUI_SOURCES third-party/include/ImGUI/*)

add_library(IMGUI STATIC ${IMGUI_SOURCES})

add_subdirectory(glimac)
add_subdirectory(code)
add_subdirectory(third-party)
add_subdirectory(third-party/include/ImGUI)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


# call the CMakeLists.txt to make the documentation (Doxygen)
# > 'make html' to generate the documentation
add_subdirectory(doc)





