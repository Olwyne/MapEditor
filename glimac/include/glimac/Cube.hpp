#pragma once

#include "Object.hpp"


using namespace glimac;



class Cube: public Object
{
  //type float so that it can multiply a glm::vec
  float m_size;
  unsigned int m_pos_in_deque;

public:
  Cube() : Object(36), m_size(0), m_pos_in_deque(0) {}
  Cube(const Param_Pos_Color param, const unsigned int nb_index, const float size, const unsigned int pos_in_deque) 
         : Object(param, nb_index), m_size(size), m_pos_in_deque(pos_in_deque) {}

  Cube(const Cube &c) : Object(c), m_size(c.m_size), m_pos_in_deque(c.m_pos_in_deque) {}
  ~Cube() override = default;

  void create_vbo_vao() override;
  void set_color(const glm::vec3 color);

  //need to be defined so that deque related functions work
  Cube& operator=(const Cube& c);
  bool operator==(const Cube& c);
  
  inline size_t get_size() { return m_size; }
  inline unsigned int get_pos_in_deque() { return m_pos_in_deque; }

};



