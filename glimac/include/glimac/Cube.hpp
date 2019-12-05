#pragma once

#include "Object.hpp"


using namespace glimac;



class Cube: public Object
{

public:
  Cube() : Object(36) {}
  Cube(Param_Pos_Color param, unsigned int nb_index) : Object(param, nb_index) {}
  ~Cube() override = default;

  void create_vbo_vao() override;
  inline glm::vec3 get_position() { return m_position; }
  void set_color(const glm::vec3 color);

};



