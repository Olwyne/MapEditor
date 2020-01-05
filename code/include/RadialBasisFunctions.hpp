#pragma once

#define GLM_FORCE_RADIANS

#include <algorithm>
#include <math.h>
#include <vector>
#include <glm/gtx/norm.hpp>
#include <eigen3/Eigen/Dense>

#include <iostream>
#include <fstream>

/// \class Phi_functor
/// \brief structure containing 4 radial basis functions
class Phi_functor
{
public:
    /// \brief return a radial basis functions
    /// \param vect1 : 2 dimension vector
    /// \param vect2 : 2 dimension vector
    /// \param e : epsilon constant
    /// \param type_function : uint representing the type of a RBF 
    template<typename T>
    T operator() (const glm::vec2 vect1, const glm::vec2 vect2, const T e, const unsigned int type_function)
    {
        T d = glm::distance2(vect1, vect2);
        T result = 0;
        
        switch (type_function)
        {
            case 0: //basic_radial_b
                result = d;
                break;
            case 1: //multiquadric
                result =  sqrt( 1+ (e*d)*(e*d) );
                break;
            case 2: //inverse_quadric
                result =  static_cast<float>(1) / ( 1+ (e*d)*(e*d) );
                break;
            case 3: //gaussian
                result =  exp(-e*d*d); 
                break;
        }
        return result;
    }
    
};



/// \brief return control points from a file
/// \param filename : file containing control points
std::vector<glm::vec2> get_control_points_RBF(const std::string &filename);

/// \brief return vector containing omega variables
/// \param control_points : vector containing control points
/// \param u_vect : vector containing generated heights of cubes
/// \param phi_function : the RBF
/// \param type_function : uint used to choose to RBF
Eigen::VectorXd get_omega_variables(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, 
                                    Phi_functor phi_function, const unsigned int type_function);

/// \brief return vector containing omega variables
/// \param control_points : vector containing control points
/// \param omegas : vector containing omega variables
/// \param all_position : vector containing (x, z) positions of world's cubes
/// \param phi_function : the RBF
/// \param type_function : uint used to choose to RBF
std::vector<float> interpolate(std::vector<glm::vec2> control_points, Eigen::VectorXd omegas, 
                               std::vector<glm::vec2> all_positions, Phi_functor phi_function, const unsigned int type_function);
