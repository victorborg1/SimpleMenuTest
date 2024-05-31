#include "SDLApp.h"

SDLApp::SDLApp() : window(nullptr), renderer(nullptr), running(true), clearColor(ImVec4(0.1f, 0.1f, 0.1f, 1.0f)), sliderValue(0.0f)
{
    items[0] = "Item 1";
    items[1] = "Item 2";
    items[2] = "Item 3";
}

SDLApp::~SDLApp()
{
    cleanup();
}

void SDLApp::initSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void SDLApp::initImGui()
{
    // vet inte
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // font (you need sdl ttf)
    // io.Fonts->AddFontFromFileTTF("src/nasa.ttf", 24.0f); // Adjust the size as needed
    // io.Fonts->Build();
}

void SDLApp::processEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        ImGui_ImplSDL2_ProcessEvent(&event);
    }
}

void SDLApp::update()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // the thing
    ImGui::Begin("Menu");
    // ImGui::Text("test");
    if (ImGui::Button("Button"))
    {
        std::cout << "feowjfefew" << std::endl;
    }
    ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 1.0f);
    ImGui::ColorEdit3("Color", (float *)&clearColor);

    // selection of items (combo box)
    if (ImGui::BeginCombo("Selection", items[currentItem]))
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            bool is_selected = (currentItem == n);
            if (ImGui::Selectable(items[n], is_selected))
            {
                currentItem = n;
            }
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::End();

    ImGui::Render();
}

void SDLApp::render()
{
    SDL_SetRenderDrawColor(renderer, clearColor.x * 255, clearColor.y * 255, clearColor.z * 255, 255);
    SDL_RenderClear(renderer);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);
}

void SDLApp::cleanup()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLApp::run()
{
    initSDL();
    initImGui();

    while (running)
    {
        frameStart = SDL_GetTicks();

        processEvents();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    cleanup();
}