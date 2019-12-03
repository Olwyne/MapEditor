#pragma once
#include "glimac/glm.hpp"

class FreeflyCamera{

private:
    glm::vec3 m_Position; //camera position
    float m_fPhi, m_fTheta; //spherical coordinates of vector F
    glm::vec3 m_FrontVector, m_LeftVector, m_UpVector; //vector F, L and U

    void computeDirectionVectors();

public:
    FreeflyCamera(); 

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;
};
