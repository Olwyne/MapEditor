#include "include/Light.hpp"
#include <../../glimac/include/glm.hpp>


void Light::create_uniform_variable_light(glimac::Program &program)
{
    //Uniform variable light
    m_uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
    m_uLightDirIntensity = glGetUniformLocation(program.getGLId(), "uLightDirIntensity");
    m_uLightPointPos1= glGetUniformLocation(program.getGLId(), "uLightPointPos1");
    m_uLightPointPos2= glGetUniformLocation(program.getGLId(), "uLightPointPos2");
    m_uAmbiantLightIntensity= glGetUniformLocation(program.getGLId(), "ambiantLightIntensity");
    m_uLightPointIntensity1= glGetUniformLocation(program.getGLId(), "uLightPointIntensity1");
    m_uLightPointIntensity2= glGetUniformLocation(program.getGLId(), "uLightPointIntensity2");

}

void Light::render_light(bool scene_modified){
    //Modified uniform variable light
    if(scene_modified)
    {
        glm::vec3 LightDir = glm::normalize(glm::vec3(10, -100, -30));;
        glUniform3f(m_uLightDir_vs, LightDir.x, LightDir.y, LightDir.z);
        glUniform1f(m_uLightDirIntensity, m_intensitySun);
        glUniform3f(m_uLightPointPos1, 15, 1, 30);
        glUniform3f(m_uLightPointPos2, 1, 15, 10);
        glUniform1f(m_uLightPointIntensity1, m_intensityPoint1);
        glUniform1f(m_uLightPointIntensity2, m_intensityPoint2);
        
        if(m_typeAmbiant==0){
            glUniform1f(m_uAmbiantLightIntensity, 0.4);
        }
        else{
            glUniform1f(m_uAmbiantLightIntensity, 0.1);
        }
    }
}