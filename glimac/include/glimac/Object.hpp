#pragma once
#include "Program.hpp"
#include "TrackballCamera.hpp"

using namespace glimac;

class Vertex3DColor
{    
 public:
    glm::vec3 m_position;
    glm::vec3 m_color;
    Vertex3DColor();
    Vertex3DColor(glm::vec3 position, glm::vec3 color)
        :m_position(position), m_color(color) {}
};


class Object
{
protected:
  GLuint m_vbo; //Vertex Buffer Object
  GLuint m_vao; //Vertex Array Object
  glm::vec3 m_position;
  glm::vec3 m_color;
  unsigned int m_nb_index; //for IBO purpose

public:
  Object() : m_nb_index(0), m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {} 
  ~Object();

  virtual void create_vbo_vao();
  virtual void render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, TrackballCamera &camera);
  virtual void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, glimac::Program &program);
  virtual unsigned int get_index();

};



