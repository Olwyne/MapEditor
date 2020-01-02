#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>

//#include <glimac/Construction.hpp>
#include <glimac/LoadSave.hpp>
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

SDL_Window* initialise_window();
SDL_GLContext initialise_context(SDL_Window* window);
ImGuiIO& initialise_ImGui(SDL_Window* window,SDL_GLContext gl_context);
void destroy_window(SDL_GLContext gl_context,SDL_Window* window);
void interface_imgui(SDL_Window* window,bool show_toolbox,bool &show_helpbox ,bool &show_savebox,bool &show_loadbox,ImVec4 clear_color,ImGuiIO& io,Construction &construction, Cursor &cursor, bool &modified_scene, bool &trackball_used,Light &light);