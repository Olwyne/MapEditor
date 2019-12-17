#include "Construction.hpp"
#include <functional>
#include <algorithm>
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


//___________________________________________interpolation function g

/*
    Little explanation: u_i will be the height of cubes, x_i their (x,z) positions
*/


Eigen::VectorXd get_omega_variables(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, 
                                    phi_functors phi_function, const unsigned int type_function)
{
    //calculate phi matrix
    const unsigned int nb_control_points = control_points.size();
    Eigen::MatrixXd phi_matrix(nb_control_points, nb_control_points);

    for(unsigned int i=0; i<nb_control_points; i++)
    {
        for(unsigned int j=0; j<nb_control_points; j++)
        {
            phi_matrix(i,j) = phi_function( control_points[i], control_points[j], 1.f, type_function);
        }
    }
    
    //calculate the inverse so that we can use the equation A⁻1 *u = omega
    Eigen::MatrixXd phi_matrix_inverse(nb_control_points, nb_control_points);
    phi_matrix_inverse = phi_matrix.inverse();


    // std::cout<<phi_matrix<<std::endl<<std::endl;
    // std::cout<<phi_matrix_inverse<<std::endl;


    return phi_matrix_inverse*u_vect;
}


std::vector<float> interpolate(Construction &construction, std::vector<glm::vec2> control_points, Eigen::VectorXd omegas, 
                               phi_functors phi_function, const unsigned int type_function)
{
    std::vector<glm::vec2> all_positions = construction.put_all_cubes_positions_in_one_vector();
    const unsigned int nb_control_points = control_points.size();
    const unsigned int nb_points_total = all_positions.size();

    //create vector to be returned
    std::vector<float> interpolation_result;
    interpolation_result.reserve(nb_points_total);
    std::fill(interpolation_result.begin(), interpolation_result.begin()+nb_points_total, 0);

    //omega * f(all_points - control_points)
    for(unsigned int i=0; i<nb_points_total; i++)
    {
        for(unsigned int j=0; j<nb_control_points; j++)
        {
            interpolation_result[i] += omegas(j)*phi_function( all_positions[i], control_points[j], 1.f, type_function );
        }

            std::cout<<"here "<<i<<" "<< interpolation_result[i]<<std::endl;

    }

    std::cout<<"__what the "<< interpolation_result[0]<<std::endl;

   
    return interpolation_result;
}


void apply_interpolation(Construction &construction, std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect,
                         phi_functors phi_function, const unsigned int type_function)
{
    Eigen::VectorXd omegas = get_omega_variables(control_points, u_vect, phi_function, type_function);
    std::vector<float> interpolation_result = interpolate(construction, control_points, omegas, phi_function, type_function);

    std::cout << "interpol vect "<< interpolation_result[0] << std::endl;
    std::cout << "interpol vect "<< interpolation_result[1] << std::endl;
    std::cout << "interpol vect "<< interpolation_result[2] << std::endl;
    std::cout << "interpol vect "<< interpolation_result[3] << std::endl;
    std::cout << "interpol vect "<< interpolation_result[4] << std::endl;

    unsigned int interpolation_it = 0;
    for(unsigned int i=0; i<construction.get_length(); i++)
    {
        for(unsigned int j=0; j<construction.get_width(); j++)
        {
            for(unsigned int k=0; k<construction.get_height(); k++)
            {
                construction.get_cubes()(i,j).at(k).set_height(interpolation_result[interpolation_it]);
                if (construction.get_cubes()(i,j).at(k).is_invisible()) construction.get_cubes()(i,j).at(k).set_invisible(0);
                //std::cout << "height is "<<interpolation_result[interpolation_it]<< std::endl;
                interpolation_it++;
            }
        }
    }
}


