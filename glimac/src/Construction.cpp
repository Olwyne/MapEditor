#include <glimac/Construction.hpp>
#include <iostream>

Construction::Construction()
{
    m_all_cubes.reserve(150); //<-------CHANGE THIS, maybe set another limit?
    //create 3 layers of cubes
    for (unsigned int layer=0; layer<3; layer++)
    {
        for(unsigned int i=0; i<5; i++)
        {
            for(unsigned int j=0; j<5; j++)
            {
                m_all_cubes.push_back( Cube(Param_Pos_Color(glm::vec3(i,0,j),glm::vec3(0.2,1,0)), 36) );
            }
        }
    } 
}


void Construction::add_cube(glm::vec3 position)
{
    //check if you're in the limits of the world?? <----------------CHANGE THIS
    //check if there's a cube on top?
    std::cout << "size__________" << m_all_cubes.size() << std::endl;

    m_all_cubes.push_back(Cube (Param_Pos_Color(position, glm::vec3(0,1,1)), 36) );
    std::cout << "added" << std::endl;
    std::cout << "size__________" << m_all_cubes.size() << std::endl;

}
