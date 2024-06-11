#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "loadTexture.h"

SDL_Rect Sprite(int x, int y, int w, int h)
{
    SDL_Rect spriteClip;

    spriteClip.x = x;
    spriteClip.y = y;
    spriteClip.w = w;
    spriteClip.h = h;

    return spriteClip;
}

int main(int argc, char *args[])
{

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        std::cout << "Could Not Initialize SDL " << SDL_GetError() << std::endl;
    }

    else
    {
        const int screenWidth = 640;
        const int screenHeight = 300;

        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        LoadTexture texture;

        SDL_Rect SpriteClip;

        window = SDL_CreateWindow("Pacman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

        if (!window)
        {
            std::cout << "Window Could Not be Displayed " << SDL_GetError() << std::endl;
        }
        else
        {

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (!renderer)
            {
                std::cout << "Renderer Cannot Be Created " << std::endl;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image Could Not Be Initialized " << IMG_GetError() << std::endl;
                };

                std::string Path = "pacmanPack/BigCoin.png";

                if (!texture.LoadTextureFromFile(Path, renderer, 4, 4))
                {
                    std::cout << "Texture Could Not be Loaded From File " << std::endl;

                    exit(0);
                }
                else
                {
                    std::cout << texture.GetHeight() << texture.GetWidth() << std::endl;
                    SpriteClip = Sprite(0, 0, 16, 16);
                }
            }

            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                        quit = true;

                    else if (e.type == SDL_KEYDOWN)
                    {

                        switch (e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            std::cout << "Up Function Called " << std::endl;
                            break;

                        case SDLK_DOWN:
                            std::cout << "Down Function Called " << std::endl;
                            break;

                        case SDLK_LEFT:
                            std::cout << "Left Function Called " << std::endl;
                            break;

                        case SDLK_RIGHT:
                            std::cout << "Right Function Called " << std::endl;
                            break;
                        }
                    }
                }

                SDL_RenderClear(renderer);
                texture.RenderOnViewPort(0, 0, screenWidth, screenHeight, renderer, SpriteClip);
                texture.ColorMod(0x89, 0x7f, 0xa8);
                SDL_RenderPresent(renderer);
            }

            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);

            window = NULL;
            renderer = NULL;

            IMG_Quit();
            SDL_Quit();
        }
    }

    return 0;
}