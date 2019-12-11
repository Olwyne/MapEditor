#pragma once
#include "glimac/glm.hpp"
#include <glimac/Camera.hpp>


class FreeflyCamera: public Camera
{

private:
    glm::vec3 m_Position; //camera position
    float m_fPhi, m_fTheta; //spherical coordinates of vector F
    glm::vec3 m_FrontVector, m_LeftVector, m_UpVector; //vector F, L and U

    void computeDirectionVectors();

public:
    FreeflyCamera(); 

    void computeDirectionVectors(glm::vec3 &m_FrontVector, glm::vec3 &m_LeftVector, glm::vec3 &m_UpVector, 
                                 const float m_fPhi, const float m_fTheta);

    void moveLeft(float delta);
    void moveFront(float delta) override;
    void rotateLeft(float degrees) override;
    void rotateUp(float degrees) override;

    glm::mat4 getViewMatrix() const override;

    void move_camera_key_pressed(const SDL_Event &e) override;

};
