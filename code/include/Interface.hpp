#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

#include <../../glimac/include/SDLWindowManager.hpp>

#include "LoadSave.hpp"
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

/// \brief return the main window
SDL_Window* initialise_window();
/// \brief return the SDL_GLContext
/// \param window : the SDL window
SDL_GLContext initialise_context(SDL_Window* window);
/// \brief return the Imgui configuration
/// \param window : the SDL window
ImGuiIO& initialise_ImGui(SDL_Window* window, SDL_GLContext gl_context);
/// \brief destroy GL and SDL information
/// \param gl_context : the SDL_GLcontext
/// \param window : the SDL window
void destroy_window(SDL_GLContext gl_context, SDL_Window* window);
/// \brief create Imgui interface
/// \param window : the SDL window
/// \param show_toolbox : boolean used to know if we show the tool box or not
/// \param show_helpbox : boolean used to know if we show the help box or not
/// \param show_savebox : boolean used to know if we show the save scene box or not
/// \param show_loadbox : boolean used to know if we show the load scene box or not
/// \param clear_color : background color of ImGUI
/// \param io : cofiguraturation between the application and ImGUI
/// \param construction : the construction of cubes
/// \param cursor : the world's cursor
/// \param modified_scene : bool set to true so that the scene will be rerendered
/// \param trackball_used : bool used to know if the trackball camera is used or not
/// \param light : the world's light
void interface_imgui(SDL_Window* window, bool show_toolbox, bool &show_helpbox, bool &show_savebox, 
                     bool &show_loadbox, ImVec4 clear_color, ImGuiIO& io, Construction &construction, 
                     Cursor &cursor, bool &modified_scene, bool &trackball_used, Light &light);