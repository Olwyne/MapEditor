#pragma once

#include "Cube.hpp"
#include <deque>

class Construction
{
private:
    static const unsigned int m_width = 5;
    static const unsigned int m_length = 5;
    static const unsigned int m_height = 3;
    static const unsigned int m_max_height_column = 40;
    //deque: use as a stack, makes it easier to add an delete cubes at top of a col
    //idea: each column = deque
    //explanation: a double dimension array of a deque of cubes
    std::array < std::array < std::deque<Cube>, m_max_height_column >, m_length*m_width > m_all_cubes; 

public:
    Construction();

    //inline std::deque <Cube> get_cubes() { return m_all_cubes; }

    //from a position, find what column of cubes the cursor is
    const glm::vec2 find_column(const glm::vec3 position);

    void add_cube(const glm::vec3 position);
    void delete_cube(const glm::vec3 position);
    void extrude_cube(const glm::vec3 position);
    void dig_cube(const glm::vec3 position);
};