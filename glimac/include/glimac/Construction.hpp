#pragma once

#include "Cube.hpp"
#include "Cursor.hpp"
#include <deque>
#include <eigen3/Eigen/Dense>


class Construction
{
private:
    static const unsigned int m_width = 5;
    static const unsigned int m_length = 5;
    static const unsigned int m_height = 3;
    static const unsigned int m_max_cubes_in_column = 40;
    //deque: makes it easier to add an delete cubes at top of a col
    //idea: each column = deque
    Eigen::Matrix <std::deque<Cube>, m_width, m_height> m_all_cubes;

public:
    Construction();

    //inline std::deque <Cube> get_cubes() { return m_all_cubes; }

    //from a cursor's position, send deque of cubes of the corresponding column
    std::deque<Cube> get_column(Cursor &cursor);

    bool is_there_a_cube(Cursor &cursor);

    void add_cube(Cursor &cursor);
    void delete_cube(Cursor &cursor);
    void extrude_cube(Cursor &cursor);
    void dig_cube(Cursor &cursor);
};