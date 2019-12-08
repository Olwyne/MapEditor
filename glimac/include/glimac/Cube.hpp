#pragma once

#include "Object.hpp"


using namespace glimac;



class Cube: public Object
{
  //type float so that it can multiply a glm::vec
  float m_size;

public:
  Cube() : Object(36), m_size(0) {}
  Cube(const Param_Pos_Color param, const unsigned int nb_index, const float size) : Object(param, nb_index), m_size(size) {}
  Cube(const Cube &c) : Object(c), m_size(c.m_size) {}
  ~Cube() override = default;

  void create_vbo_vao() override;
  void set_color(const glm::vec3 color);

  //needs to be defined so that deque related functions work
  Cube& operator=(const Cube& c);
  
  inline size_t get_size() { return m_size; }

};



