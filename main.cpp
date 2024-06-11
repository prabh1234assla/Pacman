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

void TileSprites(SDL_Rect SpriteClip[], int spritesCount = 15)
{
    // 288 192
    SpriteClip[0] = Sprite(0, 0, 120, 120);
}

void AnimatedSprite(SDL_Rect SpriteClip[], int spritesCount = 8)
{
    for (int i = 0; i < spritesCount; ++i)
    {
        SpriteClip[i] = Sprite(16 * i, 0, 16, 16);
    }
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
        const int screenHeight = 350;

        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        LoadTexture texture;
        LoadTexture tilesTexture;

        // Pacman Sprite
        SDL_Rect SpriteClip[8];
        int frame = 0;
        const int spritesCount = 8;
        const int framingDelay = 800;

        // Tiles Sprite

        double d = 0;
        int x = 240;
        int y = 30;

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
                SDL_SetRenderDrawColor(renderer, 0, 0, 0xaa, 255);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image Could Not Be Initialized " << IMG_GetError() << std::endl;
                };

                std::string PacmanPath = "assets/PacMan.png";
                std::string TilesPath = "assets/Tileset.png";

                if (!texture.LoadTextureFromFile(PacmanPath, renderer, 1, 1))
                {
                    std::cout << "Pacman Texture Could Not be Loaded From File " << std::endl;

                    exit(0);
                }
                else if (!tilesTexture.LoadTextureFromFile(TilesPath, renderer, 4, 4))
                {

                    std::cout << "Tiles Texture Could Not be Loaded From File " << std::endl;

                    exit(0);
                }
                else
                {
                    // texture.setBlendMode(SDL_BLENDMODE_BLEND);

                    AnimatedSprite(SpriteClip);
                }
            }

            std::cout << tilesTexture.GetWidth() << std::endl;

            // alpha Value
            // Uint8 a = 0;

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
                            // texture.Opacity(a);
                            d = -90;
                            --y;
                            if (y <= 0)
                                y = 0;
                            break;

                        case SDLK_DOWN:
                            std::cout << "Down Function Called " << std::endl;
                            // texture.Transparency(a);
                            d = 90;
                            ++y;
                            if (y >= screenHeight)
                                y = screenHeight;
                            break;

                        case SDLK_LEFT:
                            std::cout << "Left Function Called " << std::endl;
                            d = 180;
                            --x;
                            if (x <= 0)
                                x = 0;
                            break;

                        case SDLK_RIGHT:
                            std::cout << "Right Function Called " << std::endl;
                            ++x;
                            d = 0;
                            if (x >= screenWidth)
                                x = screenWidth;
                            break;
                        }
                    }
                }

                SDL_RenderClear(renderer);

                SDL_Rect TileClip = Sprite(256, 0, 34, 32);
                tilesTexture.RenderOnViewPort(0, 0, screenWidth, screenHeight, renderer, &TileClip);
                tilesTexture.RenderOnViewPort(screenWidth - tilesTexture.GetWidth() / 4 - 102, 0, screenWidth, screenHeight, renderer, &TileClip);
                tilesTexture.RenderOnViewPort(0, screenHeight - tilesTexture.GetHeight() / 4 - 50, screenWidth, screenHeight, renderer, &TileClip);
                tilesTexture.RenderOnViewPort(screenWidth - tilesTexture.GetWidth() / 4 - 102, screenHeight - tilesTexture.GetHeight() / 4 - 50, screenWidth, screenHeight, renderer, &TileClip);
                tilesTexture.RenderOnViewPort((screenWidth - tilesTexture.GetWidth() / 4 - 102)/2, (screenHeight - tilesTexture.GetHeight() / 4 - 50)/2, screenWidth, screenHeight, renderer, &TileClip);

                SDL_Rect *currentClip = &SpriteClip[frame / framingDelay];
                texture.RenderOnViewPort(x, y, screenWidth, screenHeight, renderer, currentClip, d);

                ++frame;

                if (frame / framingDelay >= spritesCount)
                {
                    frame = 0;
                }
                // texture.setAlpha(a);
                // texture.setColorMod(0x89, 0x7f, 0xa8);
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