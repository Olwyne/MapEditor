#include "include/Object.hpp"
#include "include/Interface.hpp"
#include <iostream>

using namespace glimac;

void Object::render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, Camera &camera)
{
    glBindVertexArray(m_vao);

    glm::mat4 camera_VM = camera.getViewMatrix();

    //vertical angle of view, ratio width/height of window, near, far 
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_WIDTH/WINDOW_HEIGHT, 0.1f, 100.f); 
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
    //formula: (MV⁻1)^T
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, glm::value_ptr(ProjMatrix*camera_VM));
    glUniformMatrix4fv(uMV_location, 1, GL_FALSE, glm::value_ptr(camera_VM*MVMatrix));
    glUniformMatrix4fv(uNormal_location, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    glDrawElements(GL_TRIANGLES, get_index(), GL_UNSIGNED_INT, 0);

    //unbind vao
    glBindVertexArray(0);

}


Object::~Object()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}


void Object::create_and_render(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, Camera &camera, bool scene_modified)
{
    //only create VBO/VAO when there's been a change 
    create_vbo_vao(scene_modified);
    //but always render 
    render(uMVP_location, uMV_location, uNormal_location, camera);
}


bool Object::obj_same_pos(Object &obj)
{
    if ( m_position == obj.m_position ) return true;
    else return false;
}
