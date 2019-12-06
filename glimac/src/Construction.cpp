#include <glimac/Construction.hpp>
#include <iostream>


Construction::Construction()
{
    //create 3 layers of cubes
    for(unsigned int i=0; i<m_length; i++)
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for (unsigned int layer=0; layer<m_height; layer++)
            {
                m_all_cubes[i][j].push_back( Cube(Param_Pos_Color(glm::vec3(i,layer,j),glm::vec3(0.2,1,0)), 36) );
            }
        }
    } 
}


const glm::vec2 Construction::find_column(const glm::vec3 position)
{
    bool column_found = false;
    unsigned int i = 0;
    unsigned int j = 0;
    while ( i<m_length && j<m_width && !column_found)
    {
        if( position.x == i && position.z == j )
        {
            column_found = true;
        }
        i++;
        j++;
    }
    
    if (!column_found) return glm::vec2(0, 0);
    else return glm::vec2(i, j);
}

void Construction::add_cube(const glm::vec3 position)
{
    //make sure a cube doesn't exist
}
