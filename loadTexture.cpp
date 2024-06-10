#include <SDL2/SDL.h>
#include <iostream>

class LoadTexture{
    private:
        SDL_Texture* texture;
        int textureWidth;
        int textureHeight;

    public:
        LoadTexture(SDL_Texture* texture, int textureWidth, int textureHeight){
            this->texture = texture;
            this->textureWidth = textureWidth;
            this->textureHeight = textureHeight;
        }

        void RenderSprite(int x, int y, SDL_Rect* clip){
            SDL_Rect renderQuad = {x, y, this->textureWidth, this->textureHeight};

            if(!clip){
                renderQuad.x = clip->x;
                renderQuad.y = clip->y;
            }

            // SDL_RenderCopy(r, this->texture, clip, &renderQuad);
        }
};