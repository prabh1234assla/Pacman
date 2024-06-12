#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class LoadTexture
{
private:
    SDL_Texture *texture = NULL;
    SDL_Rect Collider;

    int textureWidth = -1;
    int textureHeight = -1;
    int scale = 0;

    int xpos = -1;
    int ypos = -1;

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

    SDL_Rect GetRect()
    {
        if (this->texture)
        {
            return this->Collider;
        }
        std::cout << "Define Texture First" << std::endl;
    }

    int GetWidth()
    {
        if (this->texture)
        {
            return this->textureWidth;
        }
        std::cout << "Define Texture First" << std::endl;

        return -1;
    }

    int GetHeight()
    {
        if (this->texture)
        {
            return this->textureHeight;
        }
        std::cout << "Define Texture First" << std::endl;

        return -1;
    }

    int GetXpos()
    {
        if (this->texture)
        {
            return this->xpos;
        }
        std::cout << "Define Texture First" << std::endl;

        return -1;
    }

    int GetYpos()
    {
        if (this->texture)
        {
            return this->ypos;
        }
        std::cout << "Define Texture First" << std::endl;

        return -1;
    }

    int GetScale()
    {
        if (this->texture)
        {
            return this->scale;
        }
        std::cout << "Define Texture First" << std::endl;

        return 0;
    }

    void Render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip, double angle = 0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {

        SDL_Rect renderQuad = {x, y, this->textureWidth, this->textureHeight};

        renderQuad.x = x;
        renderQuad.y = y;

        this->Collider.x = x;
        this->Collider.y = y;

        this->xpos = x;
        this->ypos = y;

        if (!clip)
        {
            std::cout << "Clip Was Wrong/Not Defined " << std::endl;

            renderQuad.w = this->textureWidth;
            renderQuad.h = this->textureHeight;

            this->Collider.w = this->textureWidth;
            this->Collider.h = this->textureHeight;

            SDL_RenderCopyEx(renderer, this->texture, NULL, &renderQuad, angle, center, flip);
        }
        else
        {

            renderQuad.w = clip->w * this->scale;
            renderQuad.h = clip->h * this->scale;

            this->Collider.w = clip->w * this->scale;
            this->Collider.h = clip->h * this->scale;

            SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center, flip);
        }
    };

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

    bool LoadTextureFromFile(std::string path, SDL_Renderer *renderer, int scale = 1, bool Enable = false, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0)
    {
        freeResources();

        SDL_Texture *texture = NULL;
        SDL_Surface *loadedSurface = IMG_Load(path.c_str());

        this->scale = scale;

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
                this->textureWidth = loadedSurface->w * scale;
                this->textureHeight = loadedSurface->h * scale;

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

    void Opacity(Uint8 &alpha)
    {
        if (alpha + 32 > 255)
            alpha = 255;
        else
            alpha += 32;

        this->setAlpha(alpha);
    }

    void Transparency(Uint8 &alpha)
    {
        if (alpha - 32 < 0)
            alpha = 0;
        else
            alpha -= 32;

        this->setAlpha(alpha);
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
            this->textureWidth = -1;
            this->textureHeight = -1;

            this->scale = 0;
            this->xpos = -1;
            this->ypos = -1;
        }
    }
};