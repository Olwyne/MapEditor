#pragma once
#include "glimac/glm.hpp"
#include <glimac/SDLWindowManager.hpp>

class TrackballCamera{

private:
    //distance from centre of scene, angle of camera in function of x axis, then y axis
    float m_fDistance, m_fAngleX, m_fAngleY;

public:
    TrackballCamera(const float fDistance = 5, const float fAngleX = 0, const float fAngleY = 0) 
                    : m_fDistance(fDistance), m_fAngleX(fAngleX), m_fAngleY(fAngleY){}

    void moveFront(float delta);
    void rotateLeft (float degrees);
    void rotateUp(float degrees);
    void move_camera_key_pressed(const SDL_Event &e);

    glm::mat4 getViewMatrix() const;
};