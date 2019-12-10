include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
#add_library(ImGUI ${SRC_FILES})
add_library(glad ${SRC_FILES})
