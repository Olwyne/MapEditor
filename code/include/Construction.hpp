#pragma once

#include "Cube.hpp"
#include "Cursor.hpp"
#include "RadialBasisFunctions.hpp"
#include "Light.hpp"

constexpr unsigned int world_width = 16;
constexpr unsigned int world_length = 16;
constexpr unsigned int world_max_height = 40;


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
    static const unsigned int m_width = world_width; /*!< maximum width of the construction */
    static const unsigned int m_length = world_length; /*!< maximum length of the construction */
    static const unsigned int m_height = 3; /*!< initial height of the construction */
    static const unsigned int m_max_cubes_in_column = world_max_height; /*!< maximum height of the construction */

    Eigen::Matrix <std::vector<Cube>, m_length, m_width> m_all_cubes; /*!< matrix of columns (=vectors) of cubes*/

public:
	/// \brief only constructor: creates a 3 layered construction of dimensions m_width x m_length
    Construction();

    /// \brief return the matrix of vectors of cubes
    inline Eigen::Matrix <std::vector<Cube>, m_length, m_width> get_cubes() { return m_all_cubes; }
    /// \brief return maximum width of the construction
    constexpr unsigned int get_width() const { return m_width; } 
    /// \brief return maximum length of the construction
    constexpr unsigned int get_length() const { return m_length; }
    /// \brief return initial height of the construction
    constexpr unsigned int get_height() const { return m_height; }
    /// \brief return maximum height of the construction
    constexpr unsigned int get_max_height() const { return m_max_cubes_in_column; }

    /// \brief return true if the position is valid (inside the world), false if it isn't
	/// \param position : the position vector of type glm::vec3
    bool valid_position(glm::vec3 position);
    /// \brief return the reference to the cube where the cursor is
	/// \param cursor : reference of the cursor
    Cube& cube_at_cursor(Cursor &cursor);
    /// \brief return an unsigned int matching the index of the highest cube in the column in which the cursor ir
	/// \param cursor : reference of the cursor
    unsigned int index_highest_cube_in_col(Cursor &cursor);

    /// \brief add a cube where the cursor is
	/// \param cursor : reference of the cursor
    void add_cube(Cursor &cursor);
    /// \brief delete a cube where the cursor is
	/// \param cursor : reference of the cursor
    void delete_cube(Cursor &cursor);
    /// \brief add a cube at the top of the column in which the cursor is
	/// \param cursor : reference of the cursor
    void extrude_cube(Cursor &cursor);
    /// \brief delete the cube at the top of the column in which the cursor is
	/// \param cursor : reference of the cursor
    void dig_cube(Cursor &cursor);


    /// \brief render all cubes in the world
	/// \param uMVP_location : GLint, used to create uniform variable location
    /// \param uMV_location : GLint, used to create uniform variable location
	/// \param uNormal_location : GLint, used to create uniform variable location
	/// \param camera : either Trackball or Freefly camera
	/// \param scene_modified : bool, if true means that there's been a change in the scene and it needs to be updated
    void render_all_cubes(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, Camera &camera, bool &scene_modified);

    /// \brief return a vector of vec2: basically a vector of all (x, z) positions, used for RBF purpose
    std::vector<glm::vec2> put_all_cubes_positions_in_one_vector();

    /// \brief apply interpolation on cubes of the construction thanks to Radial Basis Functions' magic
    /// \param control_points : vector of vec2 found in a txt file
    /// \param u_vect : vector used in RBF part
    /// \param phi_function : a RBF
    /// \param type_function : the index of the RBF
    void apply_interpolation(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, Phi_functor phi_function, const unsigned int type_function);

    /// \brief save the current construction (create a txt file with all its information)
    /// \param scene modified : bool set to true so that the scene will be rerendered
    void save_scene(bool &scene_modified, std::string path, std::string name);
    /// \brief load a construction (from a txt file)
    /// \param scene_modified : bool set to true so that the scene will be rerendered
    void load_scene(bool &scene_modified, std::string path, std::string name);

    /// \brief change cubes' color according to a given perimeter
    /// \param cursor : reference to the cursor 
    /// \param perimeter : int referring to the size of the zone the user wants to paint
    /// \param scene_modified : bool set to true so that the scene will be rerendered
    void paint_cubes(Cursor &cursor, int perimeter, glm::vec3 color, bool &scene_modified);

    /// \brief sets all cubes to be invisible
    void erase_all_cubes();
};