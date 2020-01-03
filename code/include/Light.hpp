#pragma once
#include <../../glimac/include/Program.hpp>
#include <iostream>

using namespace glimac;


class Light
{
    protected:
        GLuint m_uLightDir_vs;
        GLuint m_uLightIntensity;
        GLuint m_uLightPos;
        GLuint m_uAmbiantLightIntensity;
        int m_typeAmbiant;
        float m_intensitySun;


    public:
        Light():m_uLightDir_vs(0), m_uLightIntensity(0),m_typeAmbiant(0){};
        ~Light();

        void create_uniform_variable_light(Program &program);
        void render_light(bool scene_modified);

        inline GLuint get_uLightDir_vs() { return m_uLightDir_vs; }
        inline GLuint get_uLightIntensity() { return m_uLightIntensity; }
        inline int get_typeAmbiant() { return m_typeAmbiant; }
        inline float get_intensitySun() { return m_intensitySun; }

        void set_uLightDir_vs(GLint uLightDir_vs) { m_uLightDir_vs= uLightDir_vs; }
        void set_uLightIntensity(GLint uLightIntensity) { m_uLightIntensity= uLightIntensity; }
        void set_typeAmbiant(int typeAmbiant) { m_typeAmbiant=typeAmbiant; }
        void set_intensitySun(float intensitySun) { m_intensitySun=intensitySun; }

};
