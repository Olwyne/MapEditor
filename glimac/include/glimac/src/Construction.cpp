#include <glimac/Construction.hpp>
#include <stdio.h>

Construction::Construction()
{

    // //create 3 layers of cubes
    for(unsigned int i=0; i<m_length; i++) 
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for (unsigned int layer=0; layer<m_max_cubes_in_column; layer++)
            {
                Cube new_cube = Cube(Param_Pos_Color(glm::vec3(i,layer,j), glm::vec3(0.2,1,0)) );
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
        return false;
    } 
}


Cube& Construction::cube_at_cursor(Cursor &cursor)
{
    //this function is always used after having checked that the cursor's position is valid
    if(valid_position( cursor.get_position() ))
    {
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
    else return m_all_cubes(0,0).at(0);
    
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

//used to extrude and dig
unsigned int Construction::index_highest_cube_in_col(Cursor &cursor)
{
    unsigned int index_col = 39;
    if( valid_position(cursor.get_position()) )
    {
        //work out in which column the cursor is
        unsigned int x = cursor.get_position().x;
        unsigned int z = cursor.get_position().z;

        //get last element in the column, ie find highest visible cube
        //start from the top of the column 
        bool cube_found = false;
        while(index_col>=0 && !cube_found)
        {
            //if the cube is visible
            if( !m_all_cubes(x, z).at(index_col).is_invisible() ) cube_found = true;
            else index_col--;
        }
    }
    return index_col;
}


void Construction::extrude_cube(Cursor &cursor)
{
    if(valid_position( cursor.get_position() ))
    {
        unsigned int x = cursor.get_position().x;
        unsigned int z = cursor.get_position().z;
        unsigned int y = index_highest_cube_in_col(cursor);

        m_all_cubes(x,z).at(y+1).set_invisible(0);
    }
}


void Construction::dig_cube(Cursor &cursor)
{
    if(valid_position( cursor.get_position() ))
    {
        unsigned int x = cursor.get_position().x;
        unsigned int z = cursor.get_position().z;
        unsigned int y = index_highest_cube_in_col(cursor);

        m_all_cubes(x,z).at(y).set_invisible(1);
    }
}



void Construction::render_all_cubes(GLint &uMVP_location, GLint &uMV_location, GLint &uNormal_location, GLint &uTexture_location, Camera &camera, bool &scene_modified)
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
                    m_all_cubes(length,width).at(i).create_and_render(uMVP_location, uMV_location, uNormal_location, uTexture_location, camera, scene_modified);
                }
            }
        }
    }
    scene_modified=false;
}


std::vector<glm::vec2> Construction::put_all_cubes_positions_in_one_vector()
{
    std::vector<glm::vec2> vector_of_all_positions;
    for (unsigned int length=0; length<m_length; length++) 
    {
        for (unsigned int width=0; width<m_width; width++)
        {
            for(unsigned int i=0; i<m_max_cubes_in_column; i++)
            {
                glm::vec2 x_and_z;
                x_and_z.x = m_all_cubes(length,width).at(i).get_position().x;
                x_and_z.y = m_all_cubes(length,width).at(i).get_position().z;
                vector_of_all_positions.push_back(x_and_z);
            }
        }
    }

    return vector_of_all_positions;
}


void Construction::apply_interpolation(std::vector<glm::vec2> control_points, Eigen::VectorXd u_vect, phi_functors phi_function, const unsigned int type_function)
{
    std::vector<glm::vec2> all_positions = put_all_cubes_positions_in_one_vector();
    Eigen::VectorXd omegas = get_omega_variables(control_points, u_vect, phi_function, type_function);
    std::vector<float> interpolation_result = interpolate(control_points, omegas, all_positions, phi_function, type_function);

    unsigned int interpolation_it = 0;
    for(unsigned int i=0; i<m_length; i++) 
    {
        for(unsigned int j=0; j<m_width; j++)
        {
            for(unsigned int k=0; k<m_max_cubes_in_column; k++)
            {

    /*we need to transform our interpolation results into nb that can be represented in our world*/

                //if the result is very small (happens with phi_function 3)
                if(interpolation_result[interpolation_it] < 0.1 && interpolation_result[interpolation_it] > 0)
                {
                    //get mantisa of the number
                    int exponent;
                    double mantisa = frexp(interpolation_result[interpolation_it], &exponent);
                    interpolation_result[interpolation_it] = mantisa*10;
                } 

                //else using modulo is sufficient
                else interpolation_result[interpolation_it] = static_cast<unsigned int>(interpolation_result[interpolation_it]) % m_max_cubes_in_column;
                
                //apply interpolation 
                if (m_all_cubes(i,j)[ interpolation_result[interpolation_it] ].is_invisible()) 
                {
                    for(unsigned int height=0; height<interpolation_result[interpolation_it]; height++)
                        m_all_cubes(i,j)[ height ].set_invisible(0);
                }
    
                interpolation_it++;
            }
        }
    }
}


void Construction::paint_cubes(Cursor &cursor, int perimeter, glm::vec3 color, bool &scene_modified)
{
    glm::vec3 position = cube_at_cursor(cursor).get_position();

    for(int i=-perimeter; i<perimeter; i++)
        for(int j=-perimeter; j<perimeter; j++)
                for(int k=-perimeter; k<perimeter; k++)
            {
                //make sure all positions are valid = that cubes exist
                if ( valid_position(glm::vec3(position.x-i, position.y-j, position.z-k) ) )
                        m_all_cubes(position.x-i, position.z-k)[position.y-j].set_color(color);
                    
            }
    scene_modified = true;
}




