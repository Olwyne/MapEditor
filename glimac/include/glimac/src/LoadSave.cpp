#include "LoadSave.hpp"
#include <fstream>

/*

File format:

[construction.length]   [construction.width]   [construction.height]    [construction.max_cubes_in_col]

ALL CUBES' POSITIONS


*/

void save_scene(Construction &construction, const std::string &filename)
{
    //create file in which we'll store information about Construction
    std::ofstream myfile(filename);
    myfile << construction.get_length() << " " << construction.get_width() << " ";
    myfile << construction.get_height() << " " << construction.get_max_height() << std::endl;

    for(unsigned int i=0; i<construction.get_length(); i++)
    {
        for(unsigned int j=0; j<construction.get_width(); j++)
        {
            for(unsigned int k=0; k<construction.get_height(); k++)
            {
                myfile << construction.get_cubes()(i,j)[k].get_position() << std::endl;
            }
        }
    }

}



void load_scene(Construction &construction, const std::string &filename)
{
    std::ifstream myfile;
    myfile.open(filename, std::ios::in | std::ios::binary);
    if (!myfile.is_open()) 
    {
        std::cerr << "Unable to open file"<< std::endl; 
    }

    //

    // std::string line;
    // //line per line
    // while ( getline(myfile, line) )
    // {
    //     for (unsigned int i=0; i<nb_of_control_points; i++)
    //     {
    //         myfile >> control_points[i].x;
    //         myfile >> control_points[i].y;
    //     }

}


