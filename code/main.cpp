#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_sdl.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>

#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Construction.hpp>


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

namespace{
    SDL_Window* initialise_window()
    { 
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            printf("Error: %s\n", SDL_GetError());
        }

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        SDL_Window* window = SDL_CreateWindow("World Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
       
        return window;
    }
    SDL_GLContext initialise_context(SDL_Window* window){
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        // Initialize OpenGL loader
        #if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
            bool err = gl3wInit() != 0;
        #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
            bool err = glewInit() != GLEW_OK;
        #elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
            bool err = gladLoadGL() == 0;
        #else
            bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
        #endif
        if (err)
        {
            fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        }
        return gl_context;
    }
    ImGuiIO& initialise_ImGui(SDL_Window* window,SDL_GLContext gl_context){

         // Decide GL+GLSL versions
        #if __APPLE__
            // GL 3.2 Core + GLSL 150
            const char* glsl_version = "#version 150";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        #else
            // GL 3.0 + GLSL 130
            const char* glsl_version = "#version 130";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #endif

         // Setup Dear ImGui context
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsLight();
       // ImGui::StyleColorsClassic();
        
        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init(glsl_version);
        return io;
    }
}

int main(int argc, char** argv)
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


    GLint uMVP_location, uMV_location, uNormal_location;
    
    //create cursor
    Cursor cursor;  

    //create world and intial cubes
    Construction construction;

    //variables
    GLint uMVP_location, uMV_location, uNormal_location;
    
    //create uniform variables by using one cube 
    construction.get_cubes()(0,0).at(0).create_uniform_variable_location(uMVP_location, uMV_location, uNormal_location, program);

    TrackballCamera camera;


    // Main loop
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
            ImGui_ImplSDL2_ProcessEvent(&event);
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
        construction.render_all_cubes(uMVP_location, uMV_location, uNormal_location, camera);

    //create and render the cursor
        cursor.create_and_render(uMVP_location, uMV_location, uNormal_location, camera);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

