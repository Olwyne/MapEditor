#pragma once
#include "Program.hpp"
#include "TrackballCamera.hpp"

using namespace glimac;

struct Param_Pos_Color
{
    glm::vec3 m_position;
    glm::vec3 m_color;
    Param_Pos_Color();
    Param_Pos_Color(glm::vec3 position, glm::vec3 color)
        :m_position(position), m_color(color) {}
};


class Object
{
protected:
  GLuint m_vbo; //Vertex Buffer Object
  GLuint m_vao; //Vertex Array Object
  glm::vec3 m_position;
  glm::vec3 m_color;
  //can't use const because of the operator = function (Cube.hpp)
  unsigned int m_nb_index; //for IBO purpose

public:
  Object(unsigned int nb_index) : m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0,0.5,0.5)), m_nb_index(nb_index) {} 
  Object(Param_Pos_Color param, unsigned int nb_index) : m_vbo(0), m_vao(0), m_position(param.m_position), m_color(param.m_color), m_nb_index(nb_index){}
  Object(const Object &obj): m_vbo(obj.m_vbo), m_vao(obj.m_vao), m_position(obj.m_position), m_color(obj.m_color), m_nb_index(obj.m_nb_index) {}
  
  virtual ~Object();

  virtual void create_vbo_vao() {}
  virtual void render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, TrackballCamera &camera);
  virtual void create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, glimac::Program &program);
  
  //create vao, vbo, and render
  virtual void create_and_render(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, TrackballCamera &camera);

  virtual unsigned int get_index() {return m_nb_index;}
  virtual glm::vec3 get_position() { return m_position; }
  virtual glm::vec3 get_color() { return m_color; }
  virtual GLuint get_vao() { return m_vao; }
  virtual GLuint get_vbo() { return m_vbo; }

  virtual bool obj_same_pos(Object &obj);

};



