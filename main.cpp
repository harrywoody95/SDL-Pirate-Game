#include <iostream>
#include "SDL.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    //int width, height;
    //std::cout << "Enter your resolution width: ";
    //std::cin >> width;
    //std::cout << "Enter your resolution height: ";
    //std::cin >> height;

    const int FPS = 165;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    Uint32 FPSCountStartTime = SDL_GetTicks();
    int FrameCount = 0;
    int FrameTime;
    int ActualFPS;

    Game Game;
    Game.CreateGame("Pirate Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, false);
    Game.Flags.MainMenu = false;

    while (Game.IsRunning)
    {
        SDL_GetMouseState(&Game.UserInput.MousePos.x, &Game.UserInput.MousePos.y);
        FrameStart = SDL_GetTicks();

        Game.HandleWindowEvent();
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
    Game.DestroyGame();
    return 0;
}
