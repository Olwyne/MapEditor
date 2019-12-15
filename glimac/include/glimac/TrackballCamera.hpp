#pragma once
#include "glimac/glm.hpp"
#include <glimac/Camera.hpp>

class TrackballCamera: public Camera
{

private:
    //distance from centre of scene, angle of camera in function of x axis, then y axis
    float m_fDistance, m_fAngleX, m_fAngleY;

public:
    TrackballCamera() : m_fDistance(0), m_fAngleX(0), m_fAngleY(0){}
    TrackballCamera(const float fDistance, const float fAngleX, const float fAngleY) 
                    : m_fDistance(fDistance), m_fAngleX(fAngleX), m_fAngleY(fAngleY){}

    void moveFront(float delta) override;
    void rotateLeft (float degrees) override;
    void rotateUp(float degrees) override;
    void move_camera_key_pressed(const SDL_Event &e) override;

    glm::mat4 getViewMatrix() const override;
}; 