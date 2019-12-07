#pragma once

#include "Object.hpp"


using namespace glimac;



class Cube: public Object
{

public:
  Cube() : Object(36) {}
  Cube(Param_Pos_Color param, unsigned int nb_index) : Object(param, nb_index) {}
  Cube(const Cube &c) : Object(c) {}
  ~Cube() override = default;

  void create_vbo_vao() override;
  void set_color(const glm::vec3 color);

  //needs to be defined so that deque related functions work
  Cube& operator=(const Cube& c);

};



