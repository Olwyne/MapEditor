#include "Construction.hpp"
#include <functional>
#include <math.h>
#include <vector>
#include <glm/gtx/norm.hpp>

//___________________________________________radial functions

//glm::distance2(vect1, vect2);

// template<typename T>
// T basic_radial_b(T d) { return d; } 


// template<typename T>
// T multiquadric(T d)
// {
//     return sqrt( 1+ (e*d)*(e*d) );
// }


// template<typename T>
// T inverse_quadric(T d)
// {
//     return static_cast<float>(1) / ( 1+ (e*d)*(e*d) );
// }


// template<typename T>
// T gaussian(T d)
// {
//     return exp(-e*d*d); //CHANGE THIS - is it (ed)*ed or ed*d?
// }


//___________________________________________interpolation function g

// glm::vec3 get_omega_variables(std::vector<glm::vec3> control_points, std::function<T(T)> radial_function)
// {
    
// }

// template<typename T>
// T interpolate(std::vector<glm::vec3> control_points, std::function<T(T)> radial_function)
// {
//     //determine omega in the general g function
// }



/*

Ensemble P x_i = toutes les positions des cubes existants
Fonction g vérifie g(x_i)=u_i où u_i est un poids obtenu par une fonction radiale


*/