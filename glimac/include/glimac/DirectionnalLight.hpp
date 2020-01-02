#pragma once
#include "Program.hpp"

using namespace glimac;


class DirectionnalLight
{
    protected:
        GLuint m_uDiffuse;
        GLuint m_uGlossy;
        GLuint m_uShininess;
        GLuint m_uLightDir_vs;
        GLuint m_uLightIntensity;
        GLuint m_uLightPos;
        GLuint m_uAmbiantLightIntensity;


    public:
        DirectionnalLight():m_uDiffuse(0), m_uGlossy(0), m_uShininess(0), m_uLightDir_vs(0), m_uLightIntensity(0){};
        ~DirectionnalLight();

        void create_uniform_variable_light(glimac::Program &program);
        void render_DirectionnalLight();

        GLuint get_uKd() { return m_uDiffuse; }
        GLuint get_uKs() { return m_uGlossy; }
        GLuint get_uShininess() { return m_uShininess; }
        GLuint get_uLightDir_vs() { return m_uLightDir_vs; }
        GLuint get_uLightIntensity() { return m_uLightIntensity; }

        void set_uKd(GLint uDiffuse) { m_uDiffuse= uDiffuse; }
        void set_uKs(GLint uGlossy) { m_uGlossy= uGlossy; }
        void set_uShininess(GLint uShininess) { m_uShininess= uShininess; }
        void set_uLightDir_vs(GLint uLightDir_vs) { m_uLightDir_vs= uLightDir_vs; }
        void set_uLightIntensity(GLint uLightIntensity) { m_uLightIntensity= uLightIntensity; }
};
