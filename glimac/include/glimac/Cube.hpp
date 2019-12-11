#pragma once

#include "Object.hpp"


using namespace glimac;



class Cube: public Object
{
  //type float so that it can multiply a glm::vec
  float m_size;
  bool m_invisible;
  unsigned int m_type;
  GLuint m_texture;


public:
  Cube() : Object(36), m_size(0), m_invisible(1), m_type(0), m_texture(0) {}
  Cube(const Param_Pos_Color param) 
         : Object(param, 36), m_size(1), m_invisible(0), m_type(0), m_texture(0) {}

  Cube(const Cube &c) : Object(c), m_size(c.m_size), m_invisible(c.m_invisible) {}
  ~Cube() override = default;

  void create_vbo_vao() override;
  void set_color(const glm::vec3 color);
  void set_invisible(const bool invisible);
  void set_type(unsigned int type);

  //need to be defined so that vector related functions work
  Cube& operator=(const Cube& c);
  bool operator==(const Cube& c);
  
  inline size_t get_size() { return m_size; }
  inline bool is_invisible() { return m_invisible; }
  inline bool get_type() { return m_type; }

};



