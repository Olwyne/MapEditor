#pragma once

#include "Cube.hpp"
#include "Cursor.hpp"
#include "RadialBasisFunctions.hpp"


class Construction
{
private:
    static const unsigned int m_width = 15;
    static const unsigned int m_length = 15;
    static const unsigned int m_height = 3;
    static const unsigned int m_max_cubes_in_column = 60;

    //a matrix of columns(=vectors) of cubes
    Eigen::Matrix <std::vector<Cube>, m_length, m_width> m_all_cubes;

public:
    Construction();

    inline Eigen::Matrix <std::vector<Cube>, m_length, m_width> get_cubes() { return m_all_cubes; }
    inline unsigned int get_width() const { return m_width; } 
    inline unsigned int get_length() const { return m_length; }
    inline unsigned int get_height() const { return m_height; }
    inline unsigned int get_max_height() const { return m_max_cubes_in_column; }

    bool valid_position(glm::vec3 position);
    Cube& cube_at_cursor(Cursor &cursor);
    unsigned int index_highest_cube_in_col(Cursor &cursor);

    void change_color(Cursor &cursor);

    void add_cube(Cursor &cursor);
    void delete_cube(Cursor &cursor);
    void extrude_cube(Cursor &cursor);
    void dig_cube(Cursor &cursor);

    void render_all_cubes(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uTexture_location, Camera &camera, bool &scene_modified);

    //use for radial functions
    std::vector<glm::vec2> put_all_cubes_positions_in_one_vector();

    /*The following methods aren't in Construction.cpp*/
    //RBF
    void apply_interpolation(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, phi_functors phi_function, const unsigned int type_function);

    //load and save scenes
    void save_scene(bool &scene_modified,std::string path,std::string name);
    void load_scene(bool &scene_modified,std::string path,std::string name);

    //color related functions
    void paint_cubes(Cursor &cursor, int perimeter, glm::vec3 color, bool &scene_modified);
};