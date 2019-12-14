#include "Construction.hpp"
#include <functional>
#include <math.h>
#include <vector>
#include <glm/gtx/norm.hpp>
#include <eigen3/Eigen/Dense>

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

template<typename T>
Eigen::MatrixXd generate_phi_matrix(Construction &construction, 
                                    std::function<T(const glm::vec3, const glm::vec3, const T)> phi_function, 
                                    const unsigned int nb_iterations)
{
    Eigen::MatrixXd phi_matrix(nb_iterations, nb_iterations);
    std::vector<glm::vec3> all_positions = construction.put_all_cubes_positions_in_one_vector();

    for(unsigned int i=0; i<nb_iterations; i++)
    {
        for(unsigned int j=0; j<nb_iterations; j++)
        {
            phi_matrix(i,j) = phi_function( all_positions[i], all_positions[i], 1);
        }
    }

    return phi_matrix;
}


template<typename T>
Eigen::VectorXd get_omega_variables(Construction &construction, std::vector<glm::vec3> control_points, 
                              std::function<T(const glm::vec3, const glm::vec3, const T)> phi_function, 
                              const unsigned int nb_iterations)
{
    //calculate the inverse so that we can use the equation A⁻1 *u = omega
    Eigen::MatrixXd phi_matrix_inverse(nb_iterations, nb_iterations);
    phi_matrix_inverse = generate_phi_matrix(construction, phi_function, nb_iterations).inverse();
    std::vector<glm::vec3> all_positions = construction.put_all_cubes_positions_in_one_vector();

    //calculate u_i
    Eigen::VectorXd vect_u(nb_iterations);
    for(unsigned int i=0; i<nb_iterations; i++)
    {
        vect_u(i) = phi_function( all_positions[i], all_positions[i], 1); //CHANGE THIS, probs false
    }

    return phi_matrix_inverse*vect_u;
}


// template<typename T>
// std::vector<glm::vec3> interpolate(Construction construction, std::vector<glm::vec3> control_points, Eigen::VectorXd omegas, 
//                                    std::function<T(const glm::vec3, const glm::vec3, const T)> phi_function)
// {
//     std::vector<glm::vec3> interpolated_points;
//     std::vector<glm::vec3> all_positions = construction.put_all_cubes_positions_in_one_vector();
//     //omega * f(control_point - all_points)
//     for(unsigned int i=0; i<all_positions.size(); i++)
//     {
//         for(unsigned int j=0; j<control_points.size(); j++)
//         {
//             interpolated_points(j) = omegas(i)*phi_function( control_points(j), all_positions(i) );
//         }
//     }
   
//     return all_positions;
// }



/*

Ensemble P x_i = toutes les positions des cubes existants
Fonction g vérifie g(x_i)=u_i où u_i est un poids obtenu par une fonction radiale


*/