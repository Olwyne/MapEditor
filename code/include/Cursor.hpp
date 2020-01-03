
#pragma once

#include "Object.hpp"
#include "Cube.hpp"

class Cursor: public Object
{

public:
	/// \brief constructor that calls Object's constructor using 36 as the number of indexes
  Cursor() : Object(36) {} 
	/// \brief constructor that calls Object's constructor using 36 as the number of indexes and Param_Pos_color as a parameter
  Cursor(Param_Pos_Color param) : Object(param, 36) {}
  /// \brief destructor
  ~Cursor() override = default;

	/// \brief defined in Object.hpp: adapted to a cursor
  void create_vbo_vao() override;

	/// \brief change position of the cursor
  /// \param position : new position of the cursor
  void change_position(const glm::vec3 position);
  /// \brief move cursor using keyboard
  /// \param e : SDL_event which tells us what key is being pressed
  void move(SDL_Event &e, bool &modified_scene);

};

 