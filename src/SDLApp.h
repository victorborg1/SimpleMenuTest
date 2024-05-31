#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <SDL.h>
#include <iostream>
#include "windowdata.h"

class SDLApp
{
public:
    SDLApp();
    ~SDLApp();
    void run();

private:
    void initSDL();
    void initImGui();
    void processEvents();
    void update();
    void render();
    void cleanup();

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool running;
    Uint32 frameStart;
    int frameTime;
    ImVec4 clearColor;
    float sliderValue;

    static const int TARGET_FPS = 144;
    static const int FRAME_DELAY = 1000 / TARGET_FPS;
    const char *items[3]; // Combo box items
    int currentItem = 0;  // Index of the currently selected item
};