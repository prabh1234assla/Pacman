#pragma once

#include <SDL2/SDL.h>

SDL_Rect Sprite(int x, int y, int w, int h)
{
    SDL_Rect spriteClip;

    spriteClip.x = x;
    spriteClip.y = y;
    spriteClip.w = w;
    spriteClip.h = h;

    return spriteClip;
}

void VisualizeRects(SDL_Renderer *renderer, SDL_Rect *rect)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}