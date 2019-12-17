#pragma once
#include "Program.hpp"

using namespace glimac;


class DirectionnalLight
{
    protected:
        GLuint m_uKd;
        GLuint m_uKs;
        GLuint m_uShininess;
        GLuint m_uLightDir_vs;
        GLuint m_uLightIntensity;

    public:
        DirectionnalLight():m_uKd(0), m_uKs(0), m_uShininess(0), m_uLightDir_vs(0), m_uLightIntensity(0){};
        ~DirectionnalLight();

        void create_uniform_variable_light(glimac::Program &program);
        void render_DirectionnalLight();

        GLuint get_uKd() { return m_uKd; }
        GLuint get_uKs() { return m_uKs; }
        GLuint get_uShininess() { return m_uShininess; }
        GLuint get_uLightDir_vs() { return m_uLightDir_vs; }
        GLuint get_uLightIntensity() { return m_uLightIntensity; }

        void set_uKd(GLint uKd) { m_uKd= uKd; }
        void set_uKs(GLint uKs) { m_uKs= uKs; }
        void set_uShininess(GLint uShininess) { m_uShininess= uShininess; }
        void set_uLightDir_vs(GLint uLightDir_vs) { m_uLightDir_vs= uLightDir_vs; }
        void set_uLightIntensity(GLint uLightIntensity) { m_uLightIntensity= uLightIntensity; }
};
