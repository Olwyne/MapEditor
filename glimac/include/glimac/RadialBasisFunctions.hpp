#include "Construction.hpp"
#include <functional>
#include <math.h>
#include <vector>
#include <glm/gtx/norm.hpp>
#include <eigen3/Eigen/Dense>

#include <iostream>
#include <fstream>


//___________________________________________read control points

std::vector<glm::vec3> get_control_points(const std::string &filename)
{
    const unsigned int nb_of_control_points = 5;
    std::ifstream myfile;
    myfile.open(filename, std::ios::in | std::ios::binary);
    if (!myfile.is_open()) 
    {
        std::cerr << "Unable to open file"<< std::endl; //CHANGE THIS do an assert
    }

    //build and read vect components
    std::vector<glm::vec3> control_points(nb_of_control_points);
    std::string line;
    //line per line
    while ( getline(myfile, line) )
    {
        for (unsigned int i=0; i<nb_of_control_points; i++)
        {
            myfile >> control_points[i].x;
            myfile >> control_points[i].y;
            myfile >> control_points[i].z;
        }

    }

    myfile.close();
    return control_points;
}


//___________________________________________radial functions

template<typename T>
T basic_radial_b(const glm::vec3 vect1, const glm::vec3 vect2) //CHANGE THIS, no e so how functor issue 
{ 
    T d = glm::distance2(vect1, vect2);
    return d; 
} 


template<typename T>
T multiquadric(const glm::vec3 vect1, const glm::vec3 vect2, const T e) 
{
    T d = glm::distance2(vect1, vect2);
    return sqrt( 1+ (e*d)*(e*d) );
}


template<typename T>
T inverse_quadric(const glm::vec3 vect1, const glm::vec3 vect2, const T e) 
{
    T d = glm::distance2(vect1, vect2);
    return static_cast<float>(1) / ( 1+ (e*d)*(e*d) );
}


template<typename T>
T gaussian(const glm::vec3 vect1, const glm::vec3 vect2, const T e) 
{
    T d = glm::distance2(vect1, vect2);
    return exp(-e*d*d); 
}


//___________________________________________interpolation function g

template<typename T, typename U>
Eigen::VectorXd get_omega_variables(Construction &construction, std::vector<glm::vec3> control_points, 
                                    Eigen::VectorXd u_vect, U phi_function, const unsigned int nb_iterations)
{
    //calculate phi matrix
    Eigen::MatrixXd phi_matrix(nb_iterations, nb_iterations);
    std::vector<glm::vec3> all_positions = construction.put_all_cubes_positions_in_one_vector();

    for(unsigned int i=0; i<nb_iterations; i++)
    {
        for(unsigned int j=0; j<nb_iterations; j++)
        {
            phi_matrix(i,j) = phi_function( all_positions[i], all_positions[i], 1);
        }
    }
    
    //calculate the inverse so that we can use the equation A⁻1 *u = omega
    Eigen::MatrixXd phi_matrix_inverse(nb_iterations, nb_iterations);
    phi_matrix_inverse = phi_matrix.inverse();

    return phi_matrix_inverse*u_vect;
}


template<typename T, typename U>
std::vector<glm::vec3> interpolate(Construction &construction, std::vector<glm::vec3> control_points, 
                                   Eigen::VectorXd omegas, U phi_function)
{
    std::vector<glm::vec3> interpolated_points;
    std::vector<glm::vec3> all_positions = construction.put_all_cubes_positions_in_one_vector();
    //omega * f(control_point - all_points)
    for(unsigned int i=0; i<all_positions.size(); i++)
    {
        for(unsigned int j=0; j<control_points.size(); j++)
        {
            interpolated_points[j] = omegas(i)*phi_function( control_points[j], all_positions[i] );
        }
    }
   
    return interpolated_points;
}

template<typename T>
void test_RBF(Construction &construction)
{    
    std::vector<glm::vec3> control_points;
    std::vector<glm::vec3> all_positions = construction.put_all_cubes_positions_in_one_vector(); 
    const unsigned int nb_iterations = all_positions.size();
    Eigen::VectorXd u_vect(nb_iterations);

    //random shit
    glm::vec3 yi;
    glm::vec3 er;
    const T e;

    u_vect.fill(1.f);
    control_points.push_back(glm::vec3(0,0,1));
    control_points.push_back(glm::vec3(0,1,2));
    control_points.push_back(glm::vec3(2,0,1));
    control_points.push_back(glm::vec3(0,3,1));
    control_points.push_back(glm::vec3(1,0,0));


    // Eigen::VectorXd omegas = get_omega_variables(construction, control_points, u_vect, multiquadric, nb_iterations);

    // std::vector<glm::vec3> interpolated_points = interpolate(construction, control_points, omegas, multiquadric);
}

