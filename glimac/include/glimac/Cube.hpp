#pragma once

#include "Program.hpp"
#include "TrackballCamera.hpp"

namespace glimac{


//____________________________________<-------------------------CHANGE THIS, do we really need it? private?
class Vertex3DColor
{    
 public:
    glm::vec3 m_position;
    glm::vec3 m_color;
    Vertex3DColor();
    Vertex3DColor(glm::vec3 position, glm::vec3 color)
        :m_position(position), m_color(color) {}
};



class Cube
{
private:
  GLuint m_vbo; //Vertex Buffer Object
  GLuint m_vao; //Vertex Array Object
  glm::vec3 m_position;
  glm::vec3 m_color;

public:
  Cube() : m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {} 
  Cube(glm::vec3 position, glm::vec3 color) : m_vbo(0), m_vao(0), m_position(position), m_color(color) {}
  void create_vbo_vao();
  void render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, TrackballCamera &camera);
  void liberate_resources();
  void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, glimac::Program &program);

};



}