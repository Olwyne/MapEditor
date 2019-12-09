
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Construction.hpp>


#include <GL/glew.h>
#include <iostream>
#include <vector>

using namespace glimac;



//___________________________________________________________  WHERE DO WE PUT THESE FUNCTIONS?

namespace{
    SDLWindowManager initialise()
    { 
        // Initialize SDL and open a window
        SDLWindowManager windowManager(800, 800, "World Editor");

        // Initialize glew for OpenGL3+ support
        GLenum glewInitError = glewInit();
        if(GLEW_OK != glewInitError) {
            std::cerr << glewGetErrorString(glewInitError) << std::endl;
        }

        std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

        glEnable(GL_DEPTH_TEST);

        return windowManager;
    }
}

//********************************************************************************************************
//********************************************************************************************************

int main(int argc, char** argv) {

    SDLWindowManager windowManager = initialise();
        
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/simple.vs.glsl",
                              applicationPath.dirPath() + "shaders/simple.fs.glsl");
    program.use();

    std::cout << argc << std::endl; //<---------------------change this
    
    //create cursor
    Cursor cursor;  

    //create world and intial cubes
    Construction construction;

    //variables
    GLint uMVP_location, uMV_location, uNormal_location;
    unsigned int world_length = construction.get_length();
    unsigned int world_width = construction.get_width();


    //create uniform variables by using one cube 
    construction.get_cubes()(0,0).at(0).create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, program);

    TrackballCamera camera;
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        while(windowManager.pollEvent(e)) 
        {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            //repeat is important, don't add 2 cubes at once!
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
            {
                switch(e.key.keysym.sym) //<-----CHANGE THIS, ADAPT WITH IMGUI
                {
                    case SDLK_a:
                        construction.add_cube(cursor);
                        break;
                    case SDLK_b:
                        construction.delete_cube(cursor);
                        break;
                }
            }
            camera.move_camera_key_pressed(e);
            cursor.move(e);
        }

    //create and render all cubes
        for (unsigned int length=0; length<world_length; length++) 
        {
            for (unsigned int width=0; width<world_width; width++)
            {
               construction.render_all_cubes(length, width, uMVP_location, uMV_location, uNormal_location, camera);
            }
        }
    //create and render the cursor
        cursor.create_and_render(uMVP_location, uMV_location, uNormal_location, camera);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}


// ./code/main 



