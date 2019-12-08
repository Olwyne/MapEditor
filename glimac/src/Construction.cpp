#include <glimac/Construction.hpp>
#include <iostream>


Construction::Construction()
{
    // //create 3 layers of cubes
    for(unsigned int i=0; i<m_length; i++) //<----CHANGE THIS, 3 loops is bad
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for (unsigned int layer=0; layer<m_height; layer++)
            {
                Cube new_cube = Cube(Param_Pos_Color(glm::vec3(i,layer,j), glm::vec3(0.2,1,0)), 36);
                m_all_cubes(i,j).push_back(new_cube);
            }
        }
    } 
                                                 
    for(unsigned int i=0; i<m_length; i++) 
    {
        for(unsigned int j=0; j<m_width; j++)
        {
                auto column_cubes = get_column(glm::vec3(i, 0, j));
                std::deque<Cube>::iterator it; 
                //iterator to go through all cubes in each deque/column
                std::cout << "column: ";
                for (it = column_cubes.begin(); it != column_cubes.end(); ++it) 
                {
                    std::cout << " "<< (*it).get_position();
                    std::cout<<std::endl;
                }
                    
        }
    }
}


bool Construction::valid_position(glm::vec3 position)
{
    if (position.x <= m_length && position.z <= m_width) return true;
    else return false;
}


std::deque<Cube> Construction::get_column(glm::vec3 position)
{
    if (valid_position(position))
    {
        std::deque<Cube> column = get_cubes()(position.x, position.z);
        return column;

    }
    else
    {
       std::deque<Cube> empty_col; 
       return empty_col;
    }
}


bool Construction::is_there_a_cube(Cursor &cursor)
{
    bool res = false;
    unsigned int x = cursor.get_position().x;
    unsigned int y = cursor.get_position().y;
    unsigned int z = cursor.get_position().z;
    //make sure the cursor is in the world's    CHANGE THIS USE FCT UP
    if (x <= m_length && z <= m_width)
    {
        unsigned int i = 0;
        //check if the cursor's position is the same as one of the column's cube
        while (i<m_height && !res)
        {
            if(m_all_cubes(x, z).at(i).get_position().y == y) res = true; 
            else i++;
        }
    }
    
    return res;
}

