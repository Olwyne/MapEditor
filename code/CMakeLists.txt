file(GLOB HEADER_FILES include/*.hpp)
file(GLOB SRC_FILES Object.cpp Cube.cpp Cursor.cpp Interface.cpp Light.cpp LoadSave.cpp Construction.cpp RadialBasisFunctions.cpp)
file(GLOB_RECURSE SHADER_FILES *.glsl)

#_______________________________________________________________compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Werror  -Wall -O2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")


add_executable(main ${HEADER_FILES} main.cpp ${SRC_FILES} ${SHADER_FILES})
target_link_libraries(main ${ALL_LIBRARIES} IMGUI)


file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


