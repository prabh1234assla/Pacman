#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture *loadTexture(std::string path, SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface)
    {
        std::cout << "Unable To Load Image " << IMG_GetError() << std::endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (!texture)
        {
            std::cout << "Unable To Create Texture " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(loadedSurface);
    }

    return texture;
}

bool loadMedia(std::string path, SDL_Renderer *renderer)
{

    bool success = true;

    SDL_Texture *mediaTexture = loadTexture(path, renderer);

    if (!mediaTexture)
    {
        std::cout << "Failed To Load Texture Image " << SDL_GetError() << std::endl;

        success = false;
    }

    return success;
}

void close(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *mediaTexture)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(mediaTexture);

    window = NULL;
    renderer = NULL;
    mediaTexture = NULL;

    IMG_Quit();
    SDL_Quit();
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
        const int screenHeight = 400;

        bool success = true;

        SDL_Window *window = NULL;

        window = SDL_CreateWindow("Pacman Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

        if (!window)
        {
            std::cout << "Window Could Not be Displayed " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {

            SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            SDL_Texture *texture = NULL;

            if (!renderer)
            {
                std::cout << "Renderer Cannot Be Created " << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image Could Not Be Initialized " << IMG_GetError() << std::endl;
                    success = false;
                };

                std::string Path = "pacmanPack/Tileset.png";

                if (loadMedia(Path, renderer))
                {
                    std::cout << "Image Could Not be Loaded " << std::endl;
                }
                else
                {
                    SDL_Texture *texture = loadTexture(Path, renderer);
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
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);
            }

            close(window, renderer, texture);
        }
    }

    return 0;
}