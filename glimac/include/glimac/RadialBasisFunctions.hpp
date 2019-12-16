#include "Construction.hpp"
#include <functional>
#include <math.h>
#include <vector>
#include <glm/gtx/norm.hpp>
#include <eigen3/Eigen/Dense>

#include <iostream>
#include <fstream>


//___________________________________________read control points

std::vector<glm::vec2> get_control_points(const std::string &filename)
{
    const unsigned int nb_of_control_points = 5;
    std::ifstream myfile;
    myfile.open(filename, std::ios::in | std::ios::binary);
    if (!myfile.is_open()) 
    {
        std::cerr << "Unable to open file"<< std::endl; //CHANGE THIS do an assert
    }

    //build and read vect components
    std::vector<glm::vec2> control_points(nb_of_control_points);
    std::string line;
    //line per line
    while ( getline(myfile, line) )
    {
        for (unsigned int i=0; i<nb_of_control_points; i++)
        {
            myfile >> control_points[i].x;
            myfile >> control_points[i].y;
        }

    }

    myfile.close();
    return control_points;
}


//___________________________________________radial functions

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


// template<typename T>
// T basic_radial_b(const glm::vec2 vect1, const glm::vec2 vect2) 
// { 
//     T d = glm::distance2(vect1, vect2);
//     return d; 
// } 


// template<typename T>
// T multiquadric(const glm::vec2 vect1, const glm::vec2 vect2, const T e) 
// {
//     T d = glm::distance2(vect1, vect2);
//     return sqrt( 1+ (e*d)*(e*d) );
// }


// template<typename T>
// T inverse_quadric(const glm::vec2 vect1, const glm::vec2 vect2, const T e) 
// {
//     T d = glm::distance2(vect1, vect2);
//     return static_cast<float>(1) / ( 1+ (e*d)*(e*d) );
// }


// template<typename T>
// T gaussian(const glm::vec2 vect1, const glm::vec2 vect2, const T e) 
// {
//     T d = glm::distance2(vect1, vect2);
//     return exp(-e*d*d); 
// }


//___________________________________________interpolation function g

/*
    Little explanation: u_i will be the height cubes, x_i their (x,z) positions
*/


Eigen::VectorXd get_omega_variables(std::vector<glm::vec2> control_points, const unsigned int nb_control_points, 
                                    Eigen::VectorXd u_vect, phi_functors phi_function, const unsigned int type_function)
{
    //calculate phi matrix
    Eigen::MatrixXd phi_matrix(nb_control_points, nb_control_points);

    for(unsigned int i=0; i<nb_control_points; i++)
    {
        for(unsigned int j=0; j<nb_control_points; j++)
        {
            phi_matrix(i,j) = phi_function( control_points[i], control_points[j], 1, type_function);
        }
    }
    
    //calculate the inverse so that we can use the equation A⁻1 *u = omega
    Eigen::MatrixXd phi_matrix_inverse(nb_control_points, nb_control_points);
    phi_matrix_inverse = phi_matrix.inverse();

    return phi_matrix_inverse*u_vect;
}

template <typename T>
std::vector<T> interpolate(Construction &construction, std::vector<glm::vec2> control_points, const unsigned int nb_control_points,
                                   Eigen::VectorXd omegas, phi_functors phi_function, const unsigned int type_function)
{
    std::vector<T> interpolated_points(0.f);
    std::vector<glm::vec2> all_positions = construction.put_all_cubes_positions_in_one_vector();

    //omega * f(control_point - all_points)
    for(unsigned int i=0; i<all_positions.size(); i++)
    {
        for(unsigned int j=0; j<nb_control_points; j++)
        {
            interpolated_points[i] += omegas(i)*phi_function( all_positions[i], control_points[j], 1, type_function );
        }
    }
   
    return interpolated_points;
}


//this is just used to test previous functions
template<typename T>
void test_RBF(Construction &construction)
{    
    std::vector<glm::vec2> control_points;
    std::vector<glm::vec2> all_positions = construction.put_all_cubes_positions_in_one_vector(); 
    const unsigned int nb_iterations = all_positions.size();
    Eigen::VectorXd u_vect(nb_iterations);


    u_vect.fill(1.f);
    control_points.push_back(glm::vec2(0,0));
    control_points.push_back(glm::vec2(0,1));
    control_points.push_back(glm::vec2(2,0));
    control_points.push_back(glm::vec2(0,3));
    control_points.push_back(glm::vec2(1,0));



    //Eigen::VectorXd omegas = get_omega_variables(construction, control_points, u_vect, phi_functors, nb_iterations);

    // std::vector<glm::vec3> interpolated_points = interpolate(construction, control_points, omegas, multiquadric);
}

