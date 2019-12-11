#pragma once
#include <glimac/SDLWindowManager.hpp>

/* asbtract class */
class Camera
{
 public:

    virtual void moveFront(float delta)=0;
    virtual void rotateLeft (float degrees)=0;
    virtual void rotateUp(float degrees)=0;
    virtual void move_camera_key_pressed(const SDL_Event &e)=0;

    virtual glm::mat4 getViewMatrix() const=0;

};

  

