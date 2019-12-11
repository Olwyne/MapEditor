#include <glimac/Construction.hpp>
#include <iostream>
#include <algorithm>

Construction::Construction()
{
    // //create 3 layers of cubes
    for(unsigned int i=0; i<m_length; i++) //<----CHANGE THIS if possible, 3 loops is bad
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for (unsigned int layer=0; layer<m_max_cubes_in_column; layer++)
            {
                Cube new_cube = Cube(Param_Pos_Color(glm::vec3(i,layer,j), glm::vec3(0.2,1,0)));
                //make cubes over 3 initial layers invisible
                if(layer >= 3) new_cube.set_invisible(1);
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
    else
    {
        std::cerr << "your cursor is outside of the world!" << std::endl;
        return false;
    } 
}



Cube& Construction::cube_at_cursor(Cursor &cursor)
{
    //this function is always used after having checked that the cursor's position is valid

    bool res = false;
    int cube_in_column = 0;

    //these variables are mainly created to make the code easier to read
    unsigned int x = cursor.get_position().x;
    unsigned int y = cursor.get_position().y;
    unsigned int z = cursor.get_position().z;
    unsigned int vector_size = m_all_cubes(x, z).size();

    
    //check if the cursor's position is the same as one of the column's cube
    while (cube_in_column < vector_size && !res)
    {
        //if the cursor is where a cube is
        if( m_all_cubes(x, z).at(cube_in_column).obj_same_pos(cursor) ) res=true;
        else cube_in_column++;
    }
    return m_all_cubes(x, z).at(cube_in_column);
    
}


void Construction::add_cube(Cursor &cursor)
{
    //make cube visible if not already
    if( valid_position(cursor.get_position()) && cube_at_cursor(cursor).is_invisible() )
        cube_at_cursor(cursor).set_invisible(0);
}


void Construction::delete_cube(Cursor &cursor)
{
    //make cube invisible if not already  
    if( valid_position(cursor.get_position()) && !cube_at_cursor(cursor).is_invisible() )
        cube_at_cursor(cursor).set_invisible(1);
}


void Construction::extrude_cube(Cursor &cursor)
{
    //add cube at the top of the column

    if( valid_position(cursor.get_position()) )
    {
        //work out in which column the cursor is
        unsigned int x = cursor.get_position().x;
        unsigned int z = cursor.get_position().z;
        //get last element on the column, +1 so we add the cube right after
        unsigned int y = m_all_cubes(x, z).back().get_position().y +1; 

        //extrude
        m_all_cubes(x, z).at(y).set_invisible(0);
    }
}


void Construction::dig_cube(Cursor &cursor)
{
    //add cube at the top of the column

    if( valid_position(cursor.get_position()) )
    {
        unsigned int x = cursor.get_position().x;
        unsigned int z = cursor.get_position().z;
        unsigned int y = m_all_cubes(x, z).back().get_position().y;
        //dig
        m_all_cubes(x, z).at(y).set_invisible(1);
    }
}

void Construction::change_color(Cursor &cursor)
{
    if( valid_position(cursor.get_position()))
    {
        if (cube_at_cursor(cursor).get_color()==glm::vec3(0.2,1,0)) 
            cube_at_cursor(cursor).set_color( glm::vec3(1,0,0.8) );  

        else if (cube_at_cursor(cursor).get_color()==glm::vec3(1,0,0.8)) 
            cube_at_cursor(cursor).set_color( glm::vec3(0.2,1,0) );
    }
}



void Construction::render_all_cubes(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, Camera &camera)
{       
    for (unsigned int length=0; length<m_length; length++) 
    {
        for (unsigned int width=0; width<m_width; width++)
        {
            for(unsigned int i=0; i<m_max_cubes_in_column; i++)
            {
                //only render cube if it its parameter invisible is false!
                if (!m_all_cubes(length,width).at(i).is_invisible())
                {
                    m_all_cubes(length,width).at(i).create_and_render(uMVP_location, uMV_location, uNormal_location, camera);
                }
            }
        }
    }
}