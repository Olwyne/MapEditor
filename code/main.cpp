#include <glimac/Construction.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/Camera.hpp>
#include <glimac/Interface.hpp>
#include <glimac/Image.hpp>
#include <glimac/LoadSave.hpp>

#include <GL/glew.h>
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
    bool show_savebox = false;
     bool show_loadbox = false;


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
    TrackballCamera tb_camera(45,10,0);
    FreeflyCamera ff_camera;

    bool trackball_used = true;

    //mathematics part: get control points, set u vector, apply interpolation
    // std::vector<glm::vec2> control_points = get_control_points_RBF("code/txt/control_points.txt");
    // Eigen::VectorXd u_vect(5);
    // u_vect << 1, 1, 1, 1, 1;
    // phi_functors f;
    // unsigned int RBF_function = 1; //c'est 0,1,2 ou 3, voir radialbasisfunction.hpp pour le noms des fonctions
    // construction.apply_interpolation(control_points, u_vect, f, RBF_function);

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

            //press x to paint multiple cubes around the cursor
            //number 3 is the perimeter = what needs to be chosen in imgui
            //glm::vec3 is the color = needs to be chosen in imgui too
            //construction.paint_cubes(cursor, 3, glm::vec3(1,0,0), e, scene_modified);

            
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //CHANGE THIS just to test methods
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_v:
                  //      construction.save_scene(scene_modified);
                        break;
                    case SDLK_b:
                    //    construction.load_scene(scene_modified);
                        break;
                }
            }
            
        }

        interface_imgui(window, show_toolbox, show_helpbox,show_savebox, show_loadbox, clear_color, io, construction, cursor, scene_modified, trackball_used);      
        
        //create and render all cubes
        construction.render_all_cubes(uMVP_location, uMV_location, uNormal_location, uTexture_location, choose_camera(tb_camera, ff_camera, trackball_used), scene_modified);

        //create and render the cursor
        glClear(GL_DEPTH_BUFFER_BIT); //so that it's always visible
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); //so that it's wireframed
        cursor.create_and_render(uMVP_location, uMV_location, uNormal_location, uTexture_location, choose_camera(tb_camera, ff_camera, trackball_used), scene_modified);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    destroy_window(gl_context,window);

    return 0;
}