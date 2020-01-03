#pragma once

#include "Object.hpp"
#include <../../glimac/include/Image.hpp>

using namespace glimac;


class Cube: public Object
{
private:
  bool m_invisible; /*!< Visibility of the cube */
  unsigned int m_type; /*!< Type of the cube */

public:
	/// \brief constructor that sets the cube to invisible of type 0
  Cube() : Object(36), m_invisible(1), m_type(0) {}
  /// \brief constructor that uses Param_Pos_Color to set the cube to visible, and set its position and color
  Cube(const Param_Pos_Color param) 
         : Object(param, 36), m_invisible(0), m_type(0) {}
  /// \brief reference constructor
  Cube(const Cube &c) : Object(c), m_invisible(c.m_invisible) {}
  ~Cube() override = default;

	/// \brief defined in Object.hpp: adapted to a cube
  void create_vbo_vao(bool modified_scene) override;
  /// \brief set the cube's color
	/// \param color : color to set
  void set_color(const glm::vec3 color);
  /// \brief set the cube's visibility
	/// \param invisible : bool, if true the cube will be set to invisible
  void set_invisible(const bool invisible);
  /// \brief set the cube's type
	/// \param color : type to set
  glm::vec3 set_type(unsigned int type);

  /// \brief overloading of paramter '='
	/// \param c : cube 
  Cube& operator=(const Cube& c);
  /// \brief overloading of paramter '=='
	/// \param c : cube 
  bool operator==(const Cube& c);
  
  /// \brief returns true if the cube is invisible, false if not
  inline bool is_invisible() { return m_invisible; }
  /// \brief returns the type of the cube
  inline unsigned int get_type() { return m_type; }
  
};


