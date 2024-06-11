#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "loadTexture.h"
#include "motions.h"

SDL_Rect Sprite(int x, int y, int w, int h)
{
    SDL_Rect spriteClip;

    spriteClip.x = x;
    spriteClip.y = y;
    spriteClip.w = w;
    spriteClip.h = h;

    return spriteClip;
}

void TileSprites(LoadTexture &tilesTexture, SDL_Rect SpriteClip[], int screenWidth, int screenHeight, int w, int h)
{
    const int XPos = screenWidth - tilesTexture.GetWidth() / 4 - 102;
    const int YPos = screenHeight - tilesTexture.GetHeight() / 4 - 50;

    SpriteClip[0] = Sprite(0, 0, w, h);
    SpriteClip[1] = Sprite(XPos, 0, w, h);
    SpriteClip[2] = Sprite(XPos, YPos, w, h);
    SpriteClip[3] = Sprite(0, YPos, w, h);
    SpriteClip[4] = Sprite(XPos / 2, YPos / 2, w, h);
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

        // Pacman Sprite
        LoadTexture pacMantexture;
        SDL_Rect SpriteClip[8];
        int frame = 0;
        const int spritesCount = 8;
        const int framingDelay = 800;

        // Tiles Sprite
        LoadTexture tilesTexture;
        SDL_Rect TilesColliders[5];
        double d = 0;
        int x = 200;
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

                if (!pacMantexture.LoadTextureFromFile(PacmanPath, renderer, 2))
                {
                    std::cout << "Pacman Texture Could Not be Loaded From File " << std::endl;

                    exit(0);
                }
                else if (!tilesTexture.LoadTextureFromFile(TilesPath, renderer, 4))
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

            // alpha Value
            // Uint8 a = 0;
            std::cout << tilesTexture.GetWidth() << std::endl;

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
                            MoveUp(d, y, pacMantexture.GetRect(), TilesColliders);
                            break;

                        case SDLK_DOWN:
                            std::cout << "Down Function Called " << std::endl;
                            // texture.Transparency(a);
                            MoveDown(d, y, screenHeight, pacMantexture.GetRect(), TilesColliders);
                            break;

                        case SDLK_LEFT:
                            std::cout << "Left Function Called " << std::endl;
                            MoveLeft(d, x, pacMantexture.GetRect(), TilesColliders);
                            break;

                        case SDLK_RIGHT:
                            std::cout << "Right Function Called " << std::endl;
                            MoveRight(d, x, screenWidth, pacMantexture.GetRect(), TilesColliders);
                            break;
                        }
                    }
                }

                SDL_RenderClear(renderer);

                SDL_Rect TileClip = Sprite(256, 0, 34, 32);

                TileSprites(tilesTexture, TilesColliders, screenWidth, screenHeight, TileClip.w, TileClip.h);

                for (int i = 0; i < 5; ++i)
                {
                    tilesTexture.RenderOnViewPort(TilesColliders[i].x, TilesColliders[i].y, screenWidth, screenHeight, renderer, &TileClip);
                }

                SDL_Rect *currentClip = &SpriteClip[frame / framingDelay];
                pacMantexture.RenderOnViewPort(x, y, screenWidth, screenHeight, renderer, currentClip, d);

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