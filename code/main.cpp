#include <../../glimac/include/FreeflyCamera.hpp>
#include <../../glimac/include/TrackballCamera.hpp>

#include "include/Construction.hpp"
#include "include/Camera.hpp"
#include "include/Interface.hpp"
#include "include/LoadSave.hpp"
#include "include/Light.hpp"

#include <iostream>


#include <GL/glew.h>
using namespace glimac;

int main(int, char** argv)
{
    SDL_Window* window = initialise_window();
    SDL_GLContext gl_context = initialise_context(window);
    ImGuiIO& io = initialise_ImGui(window,gl_context);
           
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/lights.vs.glsl",
                              applicationPath.dirPath() + "shaders/lights.fs.glsl");
    program.use();
    // Our state
    bool show_toolbox = true;
    bool show_helpbox = false;
    bool show_savebox = false;
    bool show_loadbox = false;

    ImVec4 clear_color = ImVec4(0, 0, 0, -1);
    
    //create cursor
    Cursor cursor;  

    //create world and initial cubes
    Construction construction;
    Light lights;


    //variables
    GLint uMVP_location = glGetUniformLocation(program.getGLId(), "uMVPMatrix" );
    GLint uMV_location = glGetUniformLocation(program.getGLId(), "uMVMatrix" );
    GLint uNormal_location = glGetUniformLocation(program.getGLId(), "uNormalMatrix" );
    lights.create_uniform_variable_light(program);
    bool scene_modified = true;

    //create Cameras
    TrackballCamera tb_camera(45,10,0);
    FreeflyCamera ff_camera;

    bool trackball_used = true;

    glEnable(GL_DEPTH_TEST);

    // Main loop
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        while(SDL_PollEvent(&e)) 
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            tb_camera.move_camera_key_pressed(e);
            ff_camera.move_camera_key_pressed(e);
            cursor.move(e);
        }

        interface_imgui(window, show_toolbox, show_helpbox,show_savebox, show_loadbox, clear_color, io, construction, cursor, scene_modified, trackball_used, lights);      
        lights.render_light(scene_modified);

        //create and render the cursor
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); //so that it's wireframed
        glClear(GL_DEPTH_BUFFER_BIT); //clear depth here again so the cursor is always visible

        cursor.create_and_render(uMVP_location, uMV_location, uNormal_location, choose_camera(tb_camera, ff_camera, trackball_used), scene_modified);
        
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );


        //create and render all cubes
        construction.render_all_cubes(uMVP_location, uMV_location, uNormal_location, choose_camera(tb_camera, ff_camera, trackball_used), scene_modified);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    destroy_window(gl_context,window);

    return 0;
}