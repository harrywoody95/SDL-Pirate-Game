// SDL-Pirate-Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SDL.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    const int FPS = 165;
    const int FrameDelay = 1000 / FPS;
    Uint32 FrameStart;
    int FrameTime;
    Game Game;
    Game.CreateGame("Pirate Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 960, false);
    //Game.Flags.MainMenu = true;
    while (Game.IsRunning)
    {
        FrameStart = SDL_GetTicks();





        Game.HandleWindowEvent();
        Game.UpdateGame();
        Game.Render();








        FrameTime = SDL_GetTicks() - FrameStart;
        if (FrameDelay > FrameTime)
        {
            SDL_Delay(FrameDelay - FrameTime);
        }
    }
    Game.DestroyGame();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
