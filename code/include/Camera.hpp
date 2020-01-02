#pragma once
#include <../../glimac/include/SDLWindowManager.hpp>

/// \class Camera
/// \brief abstract class containingFreeFly and TrackBall cameras' methods' declarations
class Camera
{
 public:

    /// \brief the camera gets closer
    /// \param delta : coefficient
    virtual void moveFront(float delta)=0;
    /// \brief rotate left
    /// \param degrees : angle of rotation
    virtual void rotateLeft (float degrees)=0;
    /// \brief rotate up
    /// \param degrees : angle of rotation
    virtual void rotateUp(float degrees)=0;
    /// \brief moves the camera in function of the keys pressed
    /// \param e : SDL_event which tells us what key is being pressed
    virtual void move_camera_key_pressed(const SDL_Event &e)=0;

    /// \brief return the View Matrix of th camera
    virtual glm::mat4 getViewMatrix() const=0;

};



