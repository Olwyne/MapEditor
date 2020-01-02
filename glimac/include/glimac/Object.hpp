#pragma once
#include "Program.hpp"
#include "Camera.hpp"
#include "Light.hpp"

using namespace glimac;

/// \struct Construction
/// \brief structure containing position and color parameters (vec3 type)
struct Param_Pos_Color
{
    glm::vec3 m_position;
    glm::vec3 m_color;
    glm::vec3 m_normal;
    Param_Pos_Color();
    Param_Pos_Color(glm::vec3 position, glm::vec3 color,glm::vec3 normal)
        :m_position(position), m_color(color),m_normal(normal) {}
    Param_Pos_Color(glm::vec3 position, glm::vec3 color)
        :m_position(position), m_color(color) {}
};


/// \class Object
/// \brief class containing parameters we need to know to render any object
class Object
{
protected:
  GLuint m_vbo; /*!< Vertex Buffer Object */
  GLuint m_vao; /*!< Vertex Array Object */
  glm::vec3 m_position; /*!< Position of the object */
  glm::vec3 m_color; /*!< Color of the object */
  unsigned int m_nb_index; /*!< Number of indexes needed for the IBO */
  glm::vec3 m_normal;

public:
	/// \brief constructor that uses a uint to define the number of indexes and initialises all other attributes 
  Object(unsigned int nb_index) : m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0,0.5,0.5)), m_nb_index(nb_index) {} 
  /// \brief constructor that uses the Param_pos_color struct to defined position and color, a uint to define the number of indexes, and initialises all other attributes 
  Object(Param_Pos_Color param, unsigned int nb_index) : m_vbo(0), m_vao(0), m_position(param.m_position), m_color(param.m_color), m_nb_index(nb_index){}
  /// \brief reference constructor
  Object(const Object &obj): m_vbo(obj.m_vbo), m_vao(obj.m_vao), m_position(obj.m_position), m_color(obj.m_color), m_nb_index(obj.m_nb_index) {}
  
  /// \brief destructor 
  virtual ~Object();

	/// \brief creates the object's VBO and VAO
  /// \param bool : boolean used to work out whether the scene should be rendered or not
  virtual void create_vbo_vao(bool) {}
	/// \brief renders the object
  /// \param uMVP_location : GLint, used to create uniform variable location
  /// \param uMV_location : GLint, used to create uniform variable location
	/// \param uNormal_location : GLint, used to create uniform variable location
	/// \param camera : either Trackball or Freefly camera
	/// \param scene_modified : bool, if true means that there's been a change in the scene and it needs to be updated
  virtual void render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, Camera &camera, bool scene_modified);
  
	/// \brief creates the object's VBO and VAO
  /// \param uMVP_location : GLint, used to create uniform variable location
  /// \param uMV_location : GLint, used to create uniform variable location
	/// \param uNormal_location : GLint, used to create uniform variable location
	/// \param camera : either Trackball or Freefly camera
	/// \param scene_modified : bool, if true means that there's been a change in the scene and it needs to be updated
  virtual void create_and_render(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, Camera &camera, bool scene_modified);

	/// \brief return the object's number of indexes
  virtual unsigned int get_index() {return m_nb_index;}
  /// \brief return the object's position
  virtual glm::vec3 get_position() { return m_position; }
  virtual glm::vec3 get_normal() { return m_normal; }
	/// \brief return the object's color 
  virtual glm::vec3 get_color() { return m_color; }
  /// \brief return the object's VAO
  virtual GLuint get_vao() { return m_vao; }
  /// \brief return the object's VBO
  virtual GLuint get_vbo() { return m_vbo; }

	/// \brief return true if the object as a parameter has the same position as the current object
  virtual bool obj_same_pos(Object &obj);

};



