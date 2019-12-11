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
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0, 0, 0, -1);
    
    //create cursor
    Cursor cursor;  

    //create world and intial cubes
    Construction construction;

    //variables
    GLint uMVP_location, uMV_location, uNormal_location;
    
    //create uniform variables by using one cube 
    construction.get_cubes()(0,0).at(0).create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, program);
   //create Cameras
    TrackballCamera tb_camera(0,0,0);
   FreeflyCamera ff_camera;

    // Main loop
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        while(SDL_PollEvent(&e)) 
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
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
                    case SDLK_w:
                        construction.change_color(cursor);
                        break;
                }
            }
            tb_camera.move_camera_key_pressed(e);
            cursor.move(e);
            
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
        if (show_demo_window)
        {
            static float f = 0.0f;
            static int counter = 0;
        //create and render all cubes

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
          

        // Rendering
        ImGui::SetNextWindowBgAlpha(0.f);
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
        
        //create and render all cubes

        construction.render_all_cubes(uMVP_location, uMV_location, uNormal_location, tb_camera);

    //create and render the cursor
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); //CHANGE THIS IT IS BAD
        cursor.create_and_render(uMVP_location, uMV_location, uNormal_location, tb_camera);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    destroy_window(gl_context,window);
    
    return 0;
}