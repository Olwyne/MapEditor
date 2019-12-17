#include <glimac/Object.hpp>
#include <iostream>

using namespace glimac;

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 800; //<----------------------------CHANGE THIS


void Object::create_uniform_variable_location(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uTexture_location, Program &program)
{
    uMVP_location = glGetUniformLocation(program.getGLId(), "uMVPMatrix" );
    uMV_location = glGetUniformLocation(program.getGLId(), "uMVMatrix" );
    uNormal_location = glGetUniformLocation(program.getGLId(), "uNormalMatrix" );
    uTexture_location = glGetUniformLocation(program.getGLId(), "uTexture" );
}

void Object::render(GLint uMVP_location, GLint uMV_location, GLint uNormal_location, GLint uTexture_location, Camera &camera, bool scene_modified,DirectionnalLight light)
{

    glm::mat4 camera_VM = camera.getViewMatrix();

    //vertical angle of view, ratio width/height of window, near, far 
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), WINDOW_HEIGHT/WINDOW_WIDTH, 0.1f, 100.f); //<---- height/width change
    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -5.f));
    //formula: (MV⁻1)^T
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    
    glBindVertexArray(m_vao);

   
    
    glUniform1i(uTexture_location, 0);
    glBindTexture(GL_TEXTURE_2D, m_texture); 
     light.render_DirectionnalLight();

    glUniformMatrix4fv(uMVP_location, 1, GL_FALSE, glm::value_ptr(ProjMatrix*camera_VM));
    glUniformMatrix4fv(uMV_location, 1, GL_FALSE, glm::value_ptr(camera_VM*MVMatrix));
    glUniformMatrix4fv(uNormal_location, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    glDrawElements(GL_TRIANGLES, get_index(), GL_UNSIGNED_INT, 0);

    //unbind vao
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}


Object::~Object()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteTextures(1, &m_texture);
}


void Object::create_and_render(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uTexture_location, Camera &camera, bool scene_modified,DirectionnalLight light)
{
    create_vbo_vao(scene_modified); 
    render(uMVP_location, uMV_location, uNormal_location, uTexture_location, camera, scene_modified,light);
}


bool Object::obj_same_pos(Object &obj)
{
    if ( m_position == obj.m_position ) return true;
    else return false;
}
