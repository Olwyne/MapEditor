#pragma once

#include "Cube.hpp"
#include "Cursor.hpp"
#include <vector>
#include <eigen3/Eigen/Dense>


class Construction
{
private:
    static const unsigned int m_width = 5;
    static const unsigned int m_length = 5;
    static const unsigned int m_height = 2;
    static const unsigned int m_max_cubes_in_column = 40;

    //a matrix of columns(=vectors) of cubes
    Eigen::Matrix <std::vector<Cube>, m_length, m_width> m_all_cubes;

public:
    Construction();

    inline Eigen::Matrix <std::vector<Cube>, m_length, m_width> get_cubes() { return m_all_cubes; }
    inline unsigned int get_width() const { return m_width; } 
    inline unsigned int get_length() const { return m_length; }
    inline unsigned int get_height() const { return m_height; }

    bool valid_position(glm::vec3 position);
    Cube& cube_at_cursor(Cursor &cursor);
    unsigned int index_highest_cube_in_col(Cursor &cursor);

    void change_color(Cursor &cursor);

    void add_cube(Cursor &cursor);
    void delete_cube(Cursor &cursor);
    void extrude_cube(Cursor &cursor);
    void dig_cube(Cursor &cursor);

    void render_all_cubes(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, Camera &camera);

    //use for radial functions
    std::vector<glm::vec2> put_all_cubes_positions_in_one_vector();


};