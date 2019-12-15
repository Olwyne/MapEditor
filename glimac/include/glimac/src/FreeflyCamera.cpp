#include <glimac/FreeflyCamera.hpp>

#include <math.h>

using namespace glimac;

FreeflyCamera::FreeflyCamera(){
    m_Position = glm::vec3(0.f, 0.f, 4.f);
    float m_fPhi = M_PI;
    float m_fTheta = 0.f;
    computeDirectionVectors(m_FrontVector, m_LeftVector, m_UpVector, m_fPhi, m_fTheta);
}
 
//methods
void FreeflyCamera::computeDirectionVectors(glm::vec3 &m_FrontVector, glm::vec3 &m_LeftVector, glm::vec3 &m_UpVector, const float m_fPhi, const float m_fTheta){
    m_FrontVector = glm::vec3(cos(m_fTheta)*sin(m_fPhi), sin(m_fTheta), cos(m_fTheta)*cos(m_fPhi));
    m_LeftVector = glm::vec3(sin(m_fPhi+M_PI/2.f), 0.f, cos(m_fPhi+M_PI/2.f));
    m_UpVector = m_FrontVector*m_LeftVector;
}


void FreeflyCamera::moveLeft(const float delta){
    m_Position += delta*m_LeftVector;
}


void FreeflyCamera::moveFront(const float delta){
    m_Position += delta*m_FrontVector;
}


void FreeflyCamera::rotateLeft(const float degrees){
    m_fPhi += glm::radians(degrees);
}


void FreeflyCamera::rotateUp(const float degrees){
    m_fTheta += glm::radians(degrees);
}


glm::mat4 FreeflyCamera::getViewMatrix() const{
    return glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
}


void FreeflyCamera::move_camera_key_pressed(const SDL_Event &e)
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
            rotateLeft(1); //doesnt work
            break;
        case SDLK_d:
            rotateLeft(-1); //doesnt work
            break;
        case SDLK_z:
            rotateUp(1); //doesnt work
            break;
        case SDLK_s:
            rotateUp(-1); //doesnt work
            break;
    }
    
}


//_________________________________________

Camera& choose_camera(TrackballCamera &tb_camera, FreeflyCamera &ff_camera, const bool choice)
{
    if(choice) return tb_camera;
    else return ff_camera;
}