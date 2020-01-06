#pragma once
#include <../../glimac/include/Program.hpp>
#include <iostream>

using namespace glimac;

/// \class Light
/// \brief class containing a light's information
class Light
{
    protected:
        GLuint m_uLightDir_vs; /*!< uniform variable for the light's direction */
        GLuint m_uLightDirIntensity; /*!< uniform variable for the light's direction's intensity */
        GLuint m_uLightPointPos1; /*!< uniform variable for the 1st point of light's position */
        GLuint m_uLightPointPos2; /*!< uniform variable for the 2nd point of light's position */
        GLuint m_uAmbiantLightIntensity; /*!< uniform variable for the light's intensity */
        GLuint m_uLightPointIntensity1; /*!< uniform variable for 1st point of light's intensity */
        GLuint m_uLightPointIntensity2; /*!< uniform variable for 2nd point of light's intensity */

        int m_typeAmbience; /*!< type of ambience */
        float m_intensitySun; /*!< intensity of the sun */
        float m_intensityPoint1; /*!< intensity of the 1st point */
        float m_intensityPoint2; /*!< intensity of the 2nd point */

    public:
    	/// \brief constructor that initialises attributes to 0
        Light() : m_typeAmbience(0), m_intensitySun(0), m_intensityPoint1(0), m_intensityPoint2(0){};

        /// \brief create uniform variables for the program
        /// \param program : main program
        void create_uniform_variable_light(Program &program);
        /// \brief render light
	    /// \param scene_modified : bool set to true so that the scene will be rerendered
        void render_light(bool scene_modified);
        
        /// \brief return type of ambience
        inline int get_typeAmbience() const { return m_typeAmbience; }
        /// \brief return the intensity of the sun         
        inline float get_intensitySun() const{ return m_intensitySun; }
        /// \brief return the intensity of the 1st point         
        inline float get_intensityPoint1() const{ return m_intensityPoint1; }
        /// \brief return the intensity of the 2nd point      
        inline float get_intensityPoint2() const { return m_intensityPoint2; }

        /// \brief set ambience type
	    /// \param typeAmbience : type of ambience
        void set_typeAmbience(int typeAmbience) { m_typeAmbience=typeAmbience; }
        /// \brief set intensity of the sun
	    /// \param intensity : intensity    
        void set_intensitySun(float intensity) { m_intensitySun=intensity; }
        /// \brief set intensity of the 1st point
	    /// \param intensity : intensity      
        void set_intensityPoint1(float intensity) { m_intensityPoint1=intensity; }
        /// \brief set intensity of the 2nd point
	    /// \param intensity : intensity   
        void set_intensityPoint2(float intensity) { m_intensityPoint2=intensity; }
};
