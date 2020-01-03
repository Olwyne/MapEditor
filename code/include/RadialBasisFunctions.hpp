#pragma once

#define GLM_FORCE_RADIANS

#include <algorithm>
#include <math.h>
#include <vector>
#include <glm/gtx/norm.hpp>
#include <eigen3/Eigen/Dense>

#include <iostream>
#include <fstream>


class phi_functors
{
public:
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



/*
    Little explanation: u_i will be the height of cubes, x_i their (x,z) positions
*/

std::vector<glm::vec2> get_control_points_RBF(const std::string &filename);

Eigen::VectorXd get_omega_variables(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, 
                                    phi_functors phi_function, const unsigned int type_function);
                                    
std::vector<float> interpolate(std::vector<glm::vec2> control_points, Eigen::VectorXd omegas, 
                                      std::vector<glm::vec2> all_positions, phi_functors phi_function, const unsigned int type_function);
