
#include <glimac/Color.hpp>
#include <glimac/Construction.hpp>
#include <chrono>
#include <random>

void Construction::paint_cubes(Cursor &cursor, int perimeter, glm::vec3 color, const SDL_Event &e, bool &scene_modified)
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_x && e.key.repeat == 0) 
    {
        //get initial position of the cursor
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
}

glm::vec3 random_color()
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    //between 0 and 1 because we're dealing with colors
    std::uniform_real_distribution<float> uniformRealDistribution(0,1);

    float color_x = uniformRealDistribution(generator);
    float color_y = uniformRealDistribution(generator);
    float color_z = uniformRealDistribution(generator);

    return glm::vec3(color_x, color_y, color_z);
}

