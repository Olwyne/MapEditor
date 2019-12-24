
#pragma once

#include "Object.hpp"
#include "Cube.hpp"

class Cursor: public Object
{

public:
  Cursor() : Object(36) {} 
  Cursor(Param_Pos_Color param, unsigned int nb_index) : Object(param, nb_index) {}
  ~Cursor() override = default;

  virtual void create_vbo_vao(bool scene_modified) override;

  void change_position(const glm::vec3 position);
  //use keyboard to change the cursor's position
  void move(SDL_Event &e);

};

 