#include <glimac/Construction.hpp>
#include <iostream>


Construction::Construction()
{
    // //create 3 layers of cubes
    for(unsigned int i=0; i<m_length; i++) //<----CHANGE THIS if possible, 3 loops is bad
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for (unsigned int layer=0; layer<m_height; layer++)
            {
                Cube new_cube = Cube(Param_Pos_Color(glm::vec3(i,layer,j), glm::vec3(0.2,1,0)), 36, 1);
                m_all_cubes(i,j).push_back(new_cube);
            }
      
      }
    } 
}


bool Construction::valid_position(glm::vec3 position)
{
    //the position is considered valid if it's in the construction of cubes
    if (   position.x <= m_length && position.z <= m_width
        && position.x >= 0 && position.z >= 0
        && position.y <= m_max_cubes_in_column && position.y >= 0) return true;
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


bool Construction::is_there_a_cube(Cursor &cursor, int &position_in_deque)
{
    bool res = false;
    int cube_in_column = 0;
    position_in_deque = -1;

    //these variables are mainly created to make the code easier to read
    unsigned int x = cursor.get_position().x;
    unsigned int y = cursor.get_position().y;
    unsigned int z = cursor.get_position().z;
    unsigned int deque_size = m_all_cubes(x, z).size();

    if (valid_position(cursor.get_position()))
    {
        //check if the cursor's position is the same as one of the column's cube
        while (cube_in_column < deque_size && !res)
        {
            //if the cursor is where a cube is
            if( m_all_cubes(x, z).at(cube_in_column).obj_same_pos(cursor) ) res=true;
            else cube_in_column++;
        }
    }

    if (res) position_in_deque = cube_in_column;

    std::cout << "is there a cube? " << res << std::endl;
    
    return res;
}

void Construction::add_cube(Cursor &cursor)
{
    int position_in_deque;
    //only add a cube if there isn't one there already!
    if(!is_there_a_cube(cursor, position_in_deque) && valid_position(cursor.get_position()))
    {
        Cube new_cube = Cube(Param_Pos_Color(cursor.get_position(), glm::vec3(0.2,1,0)), 36, 1);
        m_all_cubes(cursor.get_position().x, cursor.get_position().z).push_back(new_cube);
    }
}

void Construction::delete_cube(Cursor &cursor)
{
    int position_in_deque;
    //only delete a cube if it exists (if it does the position is necessarily valid)
    if(is_there_a_cube(cursor, position_in_deque))
    {
        auto column_begin = m_all_cubes(cursor.get_position().x, cursor.get_position().z).begin();
        m_all_cubes(cursor.get_position().x, cursor.get_position().z).erase
                                                                    (column_begin + position_in_deque);
        
        std::cout << "psInDeq" << position_in_deque << std::endl;
    }
}