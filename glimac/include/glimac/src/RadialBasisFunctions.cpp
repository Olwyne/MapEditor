
#include <glimac/RadialBasisFunctions.hpp>


std::vector<glm::vec2> get_control_points_RBF(const std::string &filename)
{
    const unsigned int nb_of_control_points = 5;
    std::ifstream myfile;
    myfile.open(filename, std::ios::in | std::ios::binary);
    if (!myfile.is_open()) 
    {
        std::cerr << "Unable to open file"<< std::endl; //CHANGE THIS do an assert
    }

    //build and read vect components
    std::vector<glm::vec2> control_points;
    control_points.resize(nb_of_control_points);
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


std::vector<float> interpolate(std::vector<glm::vec2> control_points, Eigen::VectorXd omegas, 
                                      std::vector<glm::vec2> all_positions, phi_functors phi_function, const unsigned int type_function)
{
    const unsigned int nb_control_points = control_points.size();
    const unsigned int nb_points_total = all_positions.size();

    //create vector to be returned
    std::vector<float> interpolation_result;
    interpolation_result.resize(nb_points_total);
    interpolation_result.shrink_to_fit();
    std::fill(interpolation_result.begin(), interpolation_result.begin()+nb_points_total, 0);

    //omega * f(all_points - control_points)
    for(unsigned int i=0; i<nb_points_total; i++)
    {
        for(unsigned int j=0; j<nb_control_points; j++)
        {
            interpolation_result[i] += omegas(j)*phi_function( all_positions[i], control_points[j], 1.f, type_function );
        }
    }
   
    return interpolation_result;
}


