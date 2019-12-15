#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>

#include <glimac/Cube.hpp>
#include <glimac/Cursor.hpp>
#include <glimac/Construction.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

SDL_Window* initialise_window();
SDL_GLContext initialise_context(SDL_Window* window);
ImGuiIO& initialise_ImGui(SDL_Window* window,SDL_GLContext gl_context);
void destroy_window(SDL_GLContext gl_context,SDL_Window* window);
void interface_imgui(SDL_Window* window,bool show_toolbox ,ImVec4 clear_color,ImGuiIO& io,Construction &construction, Cursor &cursor, bool &modified_scene);