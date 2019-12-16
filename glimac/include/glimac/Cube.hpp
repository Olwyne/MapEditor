#pragma once

#include "Object.hpp"
#include "Image.hpp"

using namespace glimac;


class Cube: public Object
{
private:
  bool m_invisible;
  unsigned int m_type;

public:
  Cube() : Object(36), m_invisible(1), m_type(0) {}
  Cube(const Param_Pos_Color_Text param) 
         : Object(param, 36), m_invisible(0), m_type(0) {}

  Cube(const Cube &c) : Object(c), m_invisible(c.m_invisible) {}
  ~Cube() override = default;

  void create_vbo_vao(bool scene_modified) override;
  void set_color(const glm::vec3 color);
  void set_invisible(const bool invisible);
  void set_height(const unsigned int height); //used for RBF
  void set_type(unsigned int type);

  //need to be defined so that vector related functions work
  Cube& operator=(const Cube& c);
  bool operator==(const Cube& c);
  
  inline bool is_invisible() { return m_invisible; }
  inline unsigned int get_type() { return m_type; }
  
};


