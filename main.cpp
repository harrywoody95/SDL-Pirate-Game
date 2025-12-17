#include <iostream>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"
#include "SDL.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    const int FPS = 165;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    Uint32 FPSCountStartTime = SDL_GetTicks();
    int FrameCount = 0;
    int FrameTime;
    int ActualFPS;

    Game Game;
    Game.CreateGame("Pirate Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);

    //init IMGUI

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(Game.Window.GetWindow(), Game.Renderer.MainRenderer);
    ImGui_ImplSDLRenderer2_Init(Game.Renderer.MainRenderer);

    while (Game.IsRunning)
    {
        SDL_GetMouseState(&Game.UserInput.MousePos.x, &Game.UserInput.MousePos.y);
        FrameStart = SDL_GetTicks();

        Game.HandleWindowEvent();

        //begin imgui frame

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        Game.UpdateGame();
        Game.Render();

        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
        {
            SDL_Delay(FrameDelay - FrameTime);
        }

        FrameCount++;
        if (SDL_GetTicks() - FPSCountStartTime >= 1000)
        {
            ActualFPS = FrameCount; // The number of frames in the last second.
            FrameCount = 0; // Reset the frame count for the next second.
            FPSCountStartTime = SDL_GetTicks(); // Reset the timer for the next second.

            std::cout << "FPS: " << ActualFPS << std::endl; // Output the FPS.
        }
    }

    //destroy IMGui
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    Game.DestroyGame();
    return 0;
}
