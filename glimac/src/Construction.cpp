#include <glimac/Construction.hpp>
#include <iostream>
#include <algorithm>

Construction::Construction()
{
    //CHANGE THIS: maybe use a ref cube to get the index and the size variables?
    // //create 3 layers of cubes
    for(unsigned int i=0; i<m_length; i++) //<----CHANGE THIS if possible, 3 loops is bad
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for (unsigned int layer=0; layer<m_height; layer++)
            {
                Cube new_cube = Cube(Param_Pos_Color(glm::vec3(i,layer,j), glm::vec3(0.2,1,0)), 36, 1, layer);
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


//CHANGE THIS    pretty sure it is useless asf
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
    int cube_in_column = 0;

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
    
    return res;
}

void Construction::add_cube(Cursor &cursor)
{
    //only add a cube if there isn't one there already!
    if(!is_there_a_cube(cursor) && valid_position(cursor.get_position()))
    {
        //create new cube at the cursor's position and set its pos in the deque to its height in the col
        Cube new_cube = Cube(Param_Pos_Color(cursor.get_position(), glm::vec3(0.2,1,0)), 36, 1, cursor.get_position().y);
        m_all_cubes(cursor.get_position().x, cursor.get_position().z).push_back(new_cube);
    }
}



void Construction::delete_cube(Cursor &cursor)
{
    //only delete a cube if it exists (if it does the position is necessarily valid)
    if(is_there_a_cube(cursor))
    {
        //these variables are mainly created to make the code easier to read
        unsigned int x = cursor.get_position().x;
        unsigned int y = cursor.get_position().y;
        unsigned int z = cursor.get_position().z;
        

//FUNCTOR METHOD 
        Cube &cube_to_delete = m_all_cubes(x, z).at(y);
        m_all_cubes(x, z).erase( std::remove(m_all_cubes(x, z).begin(), 
                                             m_all_cubes(x, z).end(), 
                                             cube_to_delete 
                                            ),
                                m_all_cubes(x, z).end() );
        std::cout << "cursor pos " << cursor.get_position() << std::endl;
        std::cout << "cube deleted at " << cube_to_delete.get_position() << std::endl;

    
//BASIC METHOD  
        // const unsigned int position_in_deque = m_all_cubes(x, z).at(y).get_pos_in_deque();
        // get_cubes()(x, z).erase( get_cubes()(x, z).begin() + position_in_deque );


    }
}

void Construction::render_all_cubes(const unsigned int length, const unsigned int width, GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, TrackballCamera &camera)
{
    //tried using for_each but failed :-(
    for(unsigned int i=0; i<m_all_cubes(length,width).size(); i++)
    {
        m_all_cubes(length,width).at(i).create_and_render(uMVP_location, uMV_location, uNormal_location, camera);
    }
}