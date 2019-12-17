#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>

#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Construction.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Camera.hpp>
#include <glimac/Interface.hpp>
#include <glimac/RadialBasisFunctions.hpp>
#include <glimac/Image.hpp>



#include <GL/glew.h>
#include <iostream>
#include <vector>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

using namespace glimac;

int main(int, char** argv)
{
    SDL_Window* window=initialise_window();
    SDL_GLContext gl_context =initialise_context(window);
    ImGuiIO& io=initialise_ImGui(window,gl_context);
           
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/simple.vs.glsl",
                              applicationPath.dirPath() + "shaders/simple.fs.glsl");
    program.use();
    // Our state
    bool show_toolbox = true;
    bool show_helpbox = false;

    ImVec4 clear_color = ImVec4(0, 0, 0, -1);
    
    //create cursor
    Cursor cursor;  

    //create world and intial cubes
    Construction construction;

    //variables
    GLint uMVP_location, uMV_location, uNormal_location, uTexture_location;
    bool scene_modified = true;
    
    //create uniform variables by using one cube 
    construction.get_cubes()(0,0).at(0).create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, uTexture_location, program);
   
    //create Cameras
    TrackballCamera tb_camera(15,0,0);
    FreeflyCamera ff_camera;

    bool trackball_used = true;

    // std::vector<glm::vec2> control_points;
    // control_points.push_back( glm::vec2(1,0) );
    // control_points.push_back( glm::vec2(1,1) );
    // control_points.push_back( glm::vec2(0,0) );
    // control_points.push_back( glm::vec2(0,1) );
    // control_points.push_back( glm::vec2(1,2) );
    // Eigen::VectorXd u_vect(5);
    // u_vect << 1, 1, 1, 1, 1;
    // phi_functors f;
    //  apply_interpolation(construction, control_points, u_vect, f, 0);


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

            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //just to test methods
            {
                switch(e.key.keysym.sym)
                {
                       
                }
            }
            
        }

        interface_imgui(window, show_toolbox,show_helpbox ,clear_color, io, construction, cursor, scene_modified,trackball_used);      
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        
        //create and render all cubes
        construction.render_all_cubes(uMVP_location, uMV_location, uNormal_location, uTexture_location, choose_camera(tb_camera, ff_camera, trackball_used), scene_modified);

        //create and render the cursor
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); //CHANGE THIS IT IS BAD
        cursor.create_and_render(uMVP_location, uMV_location, uNormal_location, uTexture_location, choose_camera(tb_camera, ff_camera, trackball_used), scene_modified);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    destroy_window(gl_context,window);

    return 0;
}