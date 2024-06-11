#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class LoadTexture
{
private:
    SDL_Texture *texture = NULL;
    int textureWidth = 0;
    int textureHeight = 0;
    int scaleX = 0;
    int scaleY = 0;

    void Render(int x, int y, SDL_Rect *clip, SDL_Renderer *renderer, double angle, SDL_Point *center, SDL_RendererFlip flip)
    {

        SDL_Rect renderQuad = {x, y, this->textureWidth, this->textureHeight};

        if (!clip)
        {
            std::cout << "Clip Was Wrong/Not Defined " << std::endl;
        }
        else
        {

            renderQuad.x = x;
            renderQuad.y = y;
            renderQuad.w = clip->w * this->scaleX;
            renderQuad.h = clip->h * this->scaleY;
        }

        SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center, flip);
    }

public:
    SDL_Texture *GetTexture()
    {
        if (this->texture)
        {
            return this->texture;
        }
        std::cout << "Define Texture First" << std::endl;

        return NULL;
    }

    int GetWidth()
    {
        if (this->textureWidth)
        {
            return this->textureWidth;
        }
        std::cout << "Define Texture First" << std::endl;

        return -1;
    }

    int GetHeight()
    {
        if (this->textureHeight)
        {
            return this->textureHeight;
        }
        std::cout << "Define Texture First" << std::endl;

        return -1;
    }

    void RenderOnViewPort(int x, int y, int w, int h, SDL_Renderer *renderer, SDL_Rect *SpriteClip, double angle, SDL_Point *center, SDL_RendererFlip flip)
    {
        SDL_Rect viewport;

        viewport.x = x;
        viewport.y = y;
        viewport.w = w;
        viewport.h = h;

        SDL_RenderSetViewport(renderer, &viewport);

        this->Render(x, y, SpriteClip, renderer, angle, center, flip);
    }

    void setColorKey(SDL_Surface *loadedSurface, Uint8 r, Uint8 g, Uint8 b)
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));
    }

    void setColorMod(Uint8 r, Uint8 g, Uint8 b)
    {
        SDL_SetTextureColorMod(this->texture, r, g, b);
    }

    void setBlendMode(SDL_BlendMode blending)
    {
        SDL_SetTextureBlendMode(this->texture, blending);
    }

    void setAlpha(Uint8 alpha)
    {
        SDL_SetTextureAlphaMod(this->texture, alpha);
    }

    bool LoadTextureFromFile(std::string path, SDL_Renderer *renderer, int scaleX = 1, int scaleY = 1, bool Enable = false, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0)
    {
        freeResources();

        SDL_Texture *texture = NULL;
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());

        this->scaleX = scaleX;
        this->scaleY = scaleY;

        if (!loadedSurface)
        {
            std::cout << "Unable To Load Image " << IMG_GetError() << std::endl;
        }
        else
        {
            if (Enable)
            {

                this->setColorKey(loadedSurface, r, g, b);
            }

            texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

            if (!texture)
            {
                std::cout << "Unable To Create Texture " << SDL_GetError() << std::endl;
            }
            else
            {
                this->textureWidth = loadedSurface->w * scaleX;
                this->textureHeight = loadedSurface->h * scaleY;

                SDL_FreeSurface(loadedSurface);
            }
        }

        this->texture = texture;

        if (!this->texture)
        {
            std::cout << "Unable to Load Texture From File" << std::endl;
        }

        return this->texture != NULL;
    }

    void Opacity(Uint8 &a)
    {
        if (a + 32 > 255)
            a = 255;
        else
            a += 32;
    }

    void Transparency(Uint8 &a)
    {
        if (a - 32 < 0)
            a = 0;
        else
            a -= 32;
    }

    ~LoadTexture()
    {
        freeResources();
    }

    void freeResources()
    {

        if (!this->texture)
        {
            SDL_DestroyTexture(this->texture);

            this->texture = NULL;
            this->textureWidth = 0;
            this->textureHeight = 0;
        }
    }
};