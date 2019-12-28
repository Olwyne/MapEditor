#include <glimac/FreeflyCamera.hpp>

#include <math.h>

using namespace glimac;

void FreeflyCamera::computeDirectionVectors()
{
    float phi = glm::radians(m_fPhi);
    float theta = glm::radians(m_fTheta);
    m_FrontVector = glm::vec3( glm::cos(theta)*glm::sin(phi), glm::sin(theta), glm::cos(theta)*glm::cos(phi) );
    m_LeftVector = glm::vec3( glm::sin(phi + (M_PI/2)), 0, glm::cos(phi + (M_PI/2)) );
    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

FreeflyCamera::FreeflyCamera()
{
    m_Position = glm::vec3(0.0f);
    m_fPhi = M_PI;
    m_fTheta = 0.0;
    computeDirectionVectors();
}

void FreeflyCamera::moveLeft(float t)
{
    m_Position += t*m_LeftVector; 
    computeDirectionVectors();
}

void FreeflyCamera::moveFront(float t)
{
    m_Position += t*m_FrontVector;
    computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees)
{
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees)
{
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const
{
    glm::mat4 MV = glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
    return MV;
}

void FreeflyCamera::move_camera_key_pressed(const SDL_Event &e)
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
                rotateLeft(20.f);
                break;
            case SDLK_d:
                rotateLeft(-20.f);
                break;
            case SDLK_z:
                rotateUp(20.f);
                break;
            case SDLK_s:
                rotateUp(-20.f);
                break;
        }
    }   
}


//_________________________________________

Camera& choose_camera(TrackballCamera &tb_camera, FreeflyCamera &ff_camera, const bool choice)
{
    if(choice) return tb_camera;
    else return ff_camera;
}