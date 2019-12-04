#pragma once

#include "Object.hpp"


using namespace glimac;



class Cube: public Object
{

public:
  Cube() : m_nb_index(36), m_vbo(0), m_vao(0), m_position(glm::vec3(0,0,0)), m_color(glm::vec3(0.5,0.5,0.5)) {} 
  Cube(Vertex3DColor(glm::vec3 position, glm::vec3 color)) : m_vbo(0), m_vao(0), m_position(position), m_color(color) {}
  
  virtual void create_vbo_vao() override;

};



