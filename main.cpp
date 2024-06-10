#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *args[])
{
    SDL_Window *window = NULL;

    SDL_Surface *screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cout << "Could Not Initialize SDL " << SDL_GetError() << std::endl;
    }
    else
    {
        const int screenWidth = 640;
        const int screenHeight = 400;

        window = SDL_CreateWindow("Pacman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

        if (!window)
        {
            std::cout << "Window Could Not be Displayed " << SDL_GetError() << std::endl;
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(window);

            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;
                }
            }

            SDL_DestroyWindow(window);

            SDL_Quit();

            return 0;
        }
    }
}