
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>

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


    GLint uMVP_location, uMV_location, uNormal_location;
    
    //create cursor
    Cursor cursor;  
    // Param_Pos_Color cursor_data = Param_Pos_Color(glm::vec3(0,-0.3,0), glm::vec3(0,0,0.3));
    // Cursor cursor(cursor_data, 6);

    //create cubes
    unsigned int nb_cubes=3;
    std::vector <Cube> all_cubes;
    for (unsigned int i=0; i<nb_cubes; i++)
    {
        all_cubes.push_back( Cube(Param_Pos_Color(glm::vec3(0, 2*i, 0), glm::vec3(0.2 + i/5.0, i/5.0, 0.2 + i*0.1)), 36) );
    }

    for(Cube &c: all_cubes)
    {
        c.create_vbo_vao();
    }
    all_cubes[0].create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, program);


    TrackballCamera camera;
    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            camera.move_camera_key_pressed(e);
            cursor.move(e);
            cursor.create_vbo_vao();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        for(Cube &c: all_cubes)
        {
            c.render(uMVP_location, uMV_location, uNormal_location, camera);
        }

        cursor.render(uMVP_location, uMV_location, uNormal_location, camera);

        // Update the display
        windowManager.swapBuffers();
    }


    return EXIT_SUCCESS;
}


// ./code/main 



