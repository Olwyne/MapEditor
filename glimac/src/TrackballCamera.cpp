
#include <iostream>
#include "glimac/TrackballCamera.hpp"


void TrackballCamera::moveFront(float delta) { m_fDistance += delta; }
void TrackballCamera::rotateLeft(float degrees) { m_fAngleX += degrees; }
void TrackballCamera::rotateUp(float degrees) { m_fAngleY += degrees; } 

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 T = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance));
    glm::mat4 R_X = glm::rotate(glm::mat4(1.f), glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 R_Y = glm::rotate(glm::mat4(1.f), glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));

    return T*R_X*R_Y;
}
