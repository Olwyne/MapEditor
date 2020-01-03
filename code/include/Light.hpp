#pragma once
#include <../../glimac/include/Program.hpp>
#include <iostream>

using namespace glimac;


class Light
{
    protected:
    //uniform variable
        GLuint m_uLightDir_vs; //Directionnal Light
        GLuint m_uLightDirIntensity; //Intensity Directionnal Light
        GLuint m_uLightPointPos1; //Position Point light 1
        GLuint m_uLightPointPos2; // Position Point light 2
        GLuint m_uAmbiantLightIntensity; //Ambiance light intensity
        GLuint m_uLightPointIntensity1; //Intensity Point light 1
        GLuint m_uLightPointIntensity2; //Intensity Point light 2

    //variable for update light
        int m_typeAmbiant;
        float m_intensitySun;
        float m_intensityPoint1;
        float m_intensityPoint2;

    public:
        Light():m_typeAmbiant(0),m_intensitySun(0),m_intensityPoint1(0),m_intensityPoint2(0){};
        ~Light();

        void create_uniform_variable_light(Program &program);
        void render_light(bool scene_modified);

        inline int get_typeAmbiant() { return m_typeAmbiant; }
        inline float get_intensitySun() { return m_intensitySun; }
        inline float get_intensityPoint1() { return m_intensityPoint1; }
        inline float get_intensityPoint2() { return m_intensityPoint2; }

        void set_typeAmbiant(int typeAmbiant) { m_typeAmbiant=typeAmbiant; }
        void set_intensitySun(float intensity) { m_intensitySun=intensity; }
        void set_intensityPoint1(float intensity) { m_intensityPoint1=intensity; }
        void set_intensityPoint2(float intensity) { m_intensityPoint2=intensity; }


};
