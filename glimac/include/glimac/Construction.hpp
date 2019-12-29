#pragma once

#include "Cube.hpp"
#include "Cursor.hpp"
#include "RadialBasisFunctions.hpp"

// Doxygen menu
/// \mainpage
/// \tableofcontents
/// \section install_bigsec World IMaker
/// Developed by Sophie Boyer and Monica Lisacek 
/// \section install_smallsec What's it about?
/// We basically made a program that allows you to build 3D colored cubes. You can also use radial basis functions to generate an exciting and original construction of cubes.
/// \section instroduction_sec How do I use it?
/// \subsection_sec In a terminal:
/// \li cd build
/// \li cmake ../
/// \li make
/// \li ./code/main
/// \li make html to generate this documentation



/// \class Construction
/// \brief class containing all cubes and information related to the construction's dimensions


class Construction
{
private:
    static const unsigned int m_width = 15; /*!< maximum width of the construction */
    static const unsigned int m_length = 15; /*!< maximum length of the construction */
    static const unsigned int m_height = 3; /*!< initial height of the construction */
    static const unsigned int m_max_cubes_in_column = 60; /*!< maximum height of the construction */

    Eigen::Matrix <std::vector<Cube>, m_length, m_width> m_all_cubes; /*!< matrix of columns (=vectors) of cubes*/

public:
	/// \brief constructor from a size and default constructor
	/// \param size : the size of the requested vector (optional)
    Construction();

    /// \brief return the matrix of vectors of cubes
    inline Eigen::Matrix <std::vector<Cube>, m_length, m_width> get_cubes() { return m_all_cubes; }
    /// \brief return maximum width of the construction
    inline unsigned int get_width() const { return m_width; } 
    /// \brief return maximum length of the construction
    inline unsigned int get_length() const { return m_length; }
    /// \brief return initial height of the construction
    inline unsigned int get_height() const { return m_height; }
    /// \brief return maximum height of the construction
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

    //RBF
    void apply_interpolation(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, phi_functors phi_function, const unsigned int type_function);

    //load and save scenes
    void save_scene(bool &scene_modified,std::string path,std::string name);
    void load_scene(bool &scene_modified,std::string path,std::string name);

    //color related functions
    void paint_cubes(Cursor &cursor, int perimeter, glm::vec3 color, bool &scene_modified);
};