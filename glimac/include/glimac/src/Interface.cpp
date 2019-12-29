#include <glimac/Interface.hpp>
#include <iostream>
#include <chrono>
#include <ctime>


SDL_Window* initialise_window(){ 
    try{
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
          throw std::string(SDL_GetError());
        }
    }
    catch(const std::string &err){
        std::cerr<<"Error : "<< err <<std::endl;
    }


    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("World Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);
       
    return window;
}

SDL_GLContext initialise_context(SDL_Window* window){
    #if _APPLE_
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac

    #else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

    #endif

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    try{
        if(SDL_GL_CONTEXT_MAJOR_VERSION<3 && SDL_GL_CONTEXT_MINOR_VERSION<3){
           throw std::string("No good version of OPENGL");
        }
    }
    catch(const std::string &err){
        std::cerr<<"Error : "<< err <<std::endl;
    }      

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

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
    try{
        if (err)
        {
             throw std::string("Failed to initialize OpenGL loader!\n");
        }
    }
    catch(const std::string &err){
        std::cerr<<"Error : " << err << std::endl;
    }
    return gl_context;
}

ImGuiIO& initialise_ImGui(SDL_Window* window,SDL_GLContext gl_context){

    // Decide GLSL versions
    #if _APPLE_
        // GL 3.2 Core + GLSL 150
        const char* glsl_version = "#version 150";

    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
    #endif

        // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
    return io;
}

void destroy_window(SDL_GLContext gl_context,SDL_Window* window){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void interface_imgui(SDL_Window* window,bool show_toolbox,bool &show_helpbox,bool &show_savebox,bool &show_loadbox,ImVec4 clear_color, ImGuiIO& io,Construction &construction, Cursor &cursor, bool &modified_scene,bool &trackball_used){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
    if (show_toolbox)
    {
        static float f = 0.0f;
        static int counter = 0;
        //create and render all cubes

        ImGui::Begin("ToolBox", &show_toolbox);
            if (ImGui::Button("Show help")){
                show_helpbox=!show_helpbox;
            }
            ImGui::SameLine();

            if (ImGui::Button("Save scene")){
                show_savebox=!show_savebox;
            }
            ImGui::SameLine();
             if (ImGui::Button("Load scene")){
                show_loadbox=!show_loadbox;
               // construction.load_scene(modified_scene);
                modified_scene=true;
            }
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            if(!construction.valid_position(cursor.get_position())){
                ImGui::TextColored(ImVec4(1,0,0,1), "Your cursor is outside of the world !");
                ImGui::Dummy(ImVec2(0.0f, 10.0f));
            }

            if (ImGui::Button("Change camera")){
                trackball_used=!trackball_used;
            }
            ImGui::SameLine();
            if(trackball_used){
                ImGui::TextColored(ImVec4(1,0,0,1), "Trackball camera ON");
            }
            if(!trackball_used){
                ImGui::TextColored(ImVec4(1,0,0,1), "Freefly camera ON");
            }
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            ImGui::TextColored(ImVec4(1,1,0,1), "Change the world");
            if (ImGui::Button("Add Cube")){
                construction.add_cube(cursor);
                modified_scene=true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Delete Cube")){
                construction.delete_cube(cursor);
                modified_scene=true;
            }
            if (ImGui::Button("Extrude")){
                construction.extrude_cube(cursor); 
                modified_scene=true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Dig")){
                construction.dig_cube(cursor);
                modified_scene=true;
            }
            ImGui::Dummy(ImVec2(0.0f, 10.0f));

            ImGui::TextColored(ImVec4(1,1,0,1), "Select the cube's color");
            int e = construction.cube_at_cursor(cursor).get_type();
            static int perimeter=1;
            ImGui::SliderInt("Perimeter of color", &perimeter, 1, 15);



            if(ImGui::RadioButton("Red", &e, 1)){
                construction.paint_cubes(cursor, perimeter-1, construction.cube_at_cursor(cursor).set_type(e), modified_scene);   
                 modified_scene=true;
            }
            if(ImGui::RadioButton("Green", &e, 2)){
                construction.paint_cubes(cursor, perimeter-1, construction.cube_at_cursor(cursor).set_type(e), modified_scene);   
                modified_scene=true;
            }
            if(ImGui::RadioButton("Blue", &e, 3)){
                construction.paint_cubes(cursor, perimeter-1, construction.cube_at_cursor(cursor).set_type(e), modified_scene);   
                modified_scene=true;
            }
            if(ImGui::RadioButton("Random", &e, 4)){
                construction.paint_cubes(cursor, perimeter-1, construction.cube_at_cursor(cursor).set_type(e), modified_scene);   
                modified_scene=true;
            }

        ImGui::End();
    }

       if (show_savebox)
        {
            static char path_file[128] = "code/txt/";
            static char name_file[128] = "myscene";
            ImGui::Begin("Save", &show_savebox);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::TextColored(ImVec4(1,1,0,1), "Please tell me where you want your file to be saved. ex: code/txt/");
                ImGui::InputText("Path", path_file,IM_ARRAYSIZE(path_file));
                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                ImGui::TextColored(ImVec4(1,1,0,1), "What would you like to name your file?");
                ImGui::InputText("Name", name_file,IM_ARRAYSIZE(name_file));

                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                if (ImGui::Button("Validate")){

                    std::string path_string(path_file);
                    std::string name_string(name_file);
                    construction.save_scene(modified_scene,path_string,name_string);
                    modified_scene=true;  
                    show_savebox=!show_savebox;
                }
                ImGui::TextColored(ImVec4(1,1,0,1), "Please wait few seconds after validation");
            ImGui::End();
        }
        if (show_loadbox)
        {
            static char path_file[128] = "code/txt/";
            static char name_file[128] = "myscene";
            ImGui::Begin("Load", &show_savebox);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::TextColored(ImVec4(1,1,0,1), "please give me the path of the file you want to load. ex: code/txt/");
                ImGui::InputText("Path", path_file,IM_ARRAYSIZE(path_file));
                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                ImGui::TextColored(ImVec4(1,1,0,1), "what is the name of the file?");
                ImGui::InputText("Name", name_file,IM_ARRAYSIZE(name_file));

                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                if (ImGui::Button("Validate")){

                    std::string path_string(path_file);
                    std::string name_string(name_file);
                    construction.load_scene(modified_scene,path_string,name_string);
                    modified_scene=true;  
                    show_loadbox=!show_loadbox;
                }
                ImGui::TextColored(ImVec4(1,1,0,1), "Please wait few seconds after validation");
            ImGui::End();
        }
        if (show_helpbox)
        {
            ImGui::Begin("Help", &show_helpbox);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::TextColored(ImVec4(1,1,0,1), "Moving the selection cursor :");
                ImGui::Text("I : foward ");
                ImGui::Text("K : backward ");
                ImGui::Text("J : left ");
                ImGui::Text("L : right ");
                ImGui::Text("P : up ");
                ImGui::Text("M : down ");
                ImGui::Dummy(ImVec2(0.0f, 10.0f));

                ImGui::TextColored(ImVec4(1,1,0,1), "Moving camera :");
                ImGui::Text("Arrow up : foward ");
                ImGui::Text("Arrow down : backward ");
                ImGui::Text("Q : left ");
                ImGui::Text("D : right ");
                ImGui::Text("Z : up ");
                ImGui::Text("S : down ");
            ImGui::End();
        }

    //render
    ImGui::SetNextWindowBgAlpha(0.f);
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
}