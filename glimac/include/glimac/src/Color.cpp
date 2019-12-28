#include <glimac/Construction.hpp>

void Construction::paint_cubes(Cursor &cursor, unsigned int perimeter, glm::vec3 color, const SDL_Event &e, bool &scene_modified)
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w && e.key.repeat == 0) 
        cube_at_cursor(cursor).set_color(color);
    
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_x && e.key.repeat == 0) 
    {
        //get initial position of the cursor
        glm::vec3 position = cube_at_cursor(cursor).get_position();

        for(unsigned int i=0; i<perimeter; i++)
        {
            //make sure all positions are valid = that cubes exist
            if ( valid_position(glm::vec3(position.x-i, position.y-i, position.z-i) ) )
                m_all_cubes(position.x, position.z)[position.y].set_color(color);
        }
    }

    scene_modified = true;
}

void Construction::apply_random_color(Cursor &cursor)
{

}

//Améliorez ensuite ce système de manière à pouvoir choisir un diamètre délimitant la zone à l’intérieur de laquelle la coloration s’applique.
