#include "include/Light.hpp"
#include <../../glimac/include/glm.hpp>


void Light::create_uniform_variable_light(glimac::Program &program)
{
    //Obtiention des variables uniformes pour la lumière
    m_uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    m_uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
    m_uLightPos= glGetUniformLocation(program.getGLId(), "uLightPos");
    m_uAmbiantLightIntensity= glGetUniformLocation(program.getGLId(), "ambiantLightIntensity");

}

void Light::render_light(bool scene_modified){
    if(scene_modified)
    {
        glm::vec3 LightDir = glm::normalize(glm::vec3(10, -100, -30));;
        glUniform3f(m_uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform1f(m_uLightIntensity, m_intensitySun);
        glUniform3f(m_uLightPos, 1, 1, 30);
        if(m_typeAmbiant==0){
            glUniform1f(m_uAmbiantLightIntensity, 0.4);
        }
        else{
            glUniform1f(m_uAmbiantLightIntensity, 0.1);
        }

    }

}

Light::~Light()
{
 
}