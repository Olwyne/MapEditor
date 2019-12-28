#include <iostream>
#include "glimac/TrackballCamera.hpp"
#include <glimac/SDLWindowManager.hpp>
 
void TrackballCamera::moveFront(float delta) { m_fDistance += delta; }
void TrackballCamera::rotateLeft(float degrees) { m_fAngleY += degrees; }
void TrackballCamera::rotateUp(float degrees) { m_fAngleX += degrees; } 

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 T = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
    glm::mat4 R_X = glm::rotate(glm::mat4(1.f), glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 R_Y = glm::rotate(glm::mat4(1.f), glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));

    return T*R_X*R_Y;
}

void TrackballCamera::move_camera_key_pressed(const SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                moveFront(-0.1);
                break;
            case SDLK_DOWN:
                moveFront(0.1);
                break;
            case SDLK_q:
                rotateLeft(1);
                break;
            case SDLK_d:
                rotateLeft(-1);
                break;
            case SDLK_z:
                rotateUp(1);
                break;
            case SDLK_s:
                rotateUp(-1);
                break;
        }
    }
    
}
