#pragma once

#include "Cube.hpp"
#include "Cursor.hpp"
#include <deque>
#include <eigen3/Eigen/Dense>


class Construction
{
private:
    static const unsigned int m_width = 2;
    static const unsigned int m_length = 2;
    static const unsigned int m_height = 2;
    static const unsigned int m_max_cubes_in_column = 40;
    //deque: makes it easier to add an delete cubes at top of a col
    //a matrix of columns(=deques) of cubes
    Eigen::Matrix <std::deque<Cube>, m_length, m_width> m_all_cubes;

public:
    Construction();

    inline Eigen::Matrix <std::deque<Cube>, m_length, m_width> get_cubes() { return m_all_cubes; }
    inline unsigned int get_width() const { return m_width; } 
    inline unsigned int get_length() const { return m_length; }
    inline unsigned int get_height() const { return m_height; }

    bool valid_position(glm::vec3 position);

    //from any (valid) position send deque of cubes of the corresponding column
    std::deque<Cube> get_column(glm::vec3 position);

    bool is_there_a_cube(Cursor &cursor);

    void add_cube(Cursor &cursor);
    void delete_cube(Cursor &cursor);
    void extrude_cube(Cursor &cursor);
    void dig_cube(Cursor &cursor);


    void render_all_cubes(const unsigned int length, const unsigned int width, GLint &uMVP_location, 
                          GLint &uMV_location, GLint &uNormal_location, TrackballCamera &camera);


};