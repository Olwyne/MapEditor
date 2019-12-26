#include <glimac/LoadSave.hpp>
#include <fstream>

/*

File format:

[construction.length]   [construction.width]   [construction.height]    [construction.max_cubes_in_col]

ALL CUBES' POSITIONS then COLORS


*/


std::string name_file(const unsigned int load)
{
    std::string name, path;
    if (load == 1)
        std::cout << "please give me the path of the file you want to load. ex: code/txt/" << std::endl;
    else
        std::cout << "please tell me where you want your file to be saved. ex: code/txt/" << std::endl;
    
    std::cin >> path;
    std::cout << "what would you like to name your file?" << std::endl;
    std::cin >> name;
    return path + name + ".txt";
}


void Construction::save_scene(bool &scene_modified)
{
    std::string filename = name_file(0);

    //create file in which we'll store information about Construction
    std::ofstream myfile(filename);
    myfile.open(filename, std::ios::out | std::ios::binary);
    if (!myfile.is_open()) 
    {
        std::cerr << "Unable to open file"<< std::endl; 
    }

    myfile << std::endl;
    myfile << m_length << " " << m_width << " ";
    myfile << m_height << " " << m_max_cubes_in_column << std::endl;

    for(unsigned int i=0; i<m_length; i++) 
        for(unsigned int j=0; j<m_width; j++)
            for(unsigned int k=0; k<m_max_cubes_in_column; k++)
            {
                //only write information if the cube is visible
                if(!m_all_cubes(i,j)[k].is_invisible())
                {
                    //write positions
                    myfile << m_all_cubes(i,j)[k].get_position().x << " ";
                    myfile << m_all_cubes(i,j)[k].get_position().y << " ";
                    myfile << m_all_cubes(i,j)[k].get_position().z << " ";
                    //write colors
                    myfile << m_all_cubes(i,j)[k].get_color().x << " ";
                    myfile << m_all_cubes(i,j)[k].get_color().y << " ";
                    myfile << m_all_cubes(i,j)[k].get_color().z << std::endl;
                }
            }

    //so that cubes are rendered 
    scene_modified = true;
    myfile.close();
}



void Construction::load_scene(bool &scene_modified)
{
    std::string filename = name_file(1);

    //set all cubes to be invisible so we start from 0
    for(unsigned int i=0; i<m_length; i++)
        for(unsigned int j=0; j<m_width; j++)
            for(unsigned int k=0; k<m_max_cubes_in_column; k++)
            {
                if (!m_all_cubes(i,j)[k].is_invisible())
                    m_all_cubes(i,j)[k].set_invisible(1);
            }    


    //open and check file
    std::ifstream myfile;
    myfile.open(filename, std::ios::in | std::ios::binary);
    if (!myfile.is_open()) 
    {
        std::cerr << "Unable to open file"<< std::endl; 
    }

    std::string line;
    unsigned int line_nb = 0;
    //line per line
    while ( getline(myfile, line) && line_nb != 999999)
    {
        //read the first line to get construction's parameters
        if(line_nb == 0 ) 
        {
            unsigned int width, length, height, max_height;
            myfile >> length >> width >> height >> max_height;
            line_nb++;
            //if invalid numbers, stop everything
            if (length != 10 || width != 10 || height != 3 || max_height != 60)
            {
                std::cerr << "Invalid paramaters to build construction"<< std::endl; 
                line_nb = 999999;
            } 
        }
        else 
        {
            unsigned int x, y, z;
            float color_x, color_y, color_z;
            myfile >> x >> y >> z;
            m_all_cubes(x,z)[y].set_invisible(0);
            myfile >> color_x >> color_y >> color_z;
            m_all_cubes(x,z)[y].set_color( glm::vec3(color_x, color_y, color_z));
        }
    }

    //so that cubes are rendered 
    scene_modified = true;
    myfile.close();
}


