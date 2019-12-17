#include <glimac/DirectionnalLight.hpp>
#include "glimac/glm.hpp"


void DirectionnalLight::create_uniform_variable_light(glimac::Program &program)
{
    //Obtiention des variables uniformes pour la lumière
    m_uKd = glGetUniformLocation(program.getGLId(), "uKd");
    m_uKs = glGetUniformLocation(program.getGLId(), "uKs");
    m_uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    m_uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    m_uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

}

void DirectionnalLight::render_DirectionnalLight(){
    glUniform3f(m_uKd, 0.1, 0.2, 0.3); //Couleur des boules
    glUniform3f(m_uKs, 0.5, 0.0, 0.0);
    glUniform1f(m_uShininess, 32.0);
    glm::vec4 LightDir =  glm::vec4(0, 0, 0, 0.0);
    glUniform3f(m_uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
    glUniform3f(m_uLightIntensity, 20.0, 20.0, 20.0);
}

DirectionnalLight::~DirectionnalLight()
{
 
}