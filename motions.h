#pragma once

#include "collision.h"

const int Steps = 2;

void MoveUp(SDL_RendererFlip* f, double &d, int &y, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = -90;

    PacMan.y -= Steps;

    *f = SDL_FLIP_NONE;

    if (y - Steps < 0 || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Up " << std::endl;
    }
    else
    {
        y -= Steps;
    }
}

void MoveDown(SDL_RendererFlip* f, double &d, int &y, int screenHeight, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = 90;

    PacMan.y += Steps;

    *f = SDL_FLIP_NONE;

    if (y + Steps + PacMan.w > screenHeight || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Down " << std::endl;
    }
    else
    {
        y += Steps;
    }
}

void MoveLeft(SDL_RendererFlip* f, double &d, int &x, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = 180;

    PacMan.x -= Steps;

    *f = SDL_FLIP_VERTICAL;

    if (x - Steps < 0 || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Left " << std::endl;
    }
    else
    {
        x -= Steps;
    }
}

void MoveRight(SDL_RendererFlip* f, double &d, int &x, int screenWidth, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = 0;

    PacMan.x += Steps;

    *f = SDL_FLIP_NONE;

    if (x + Steps + PacMan.w > screenWidth || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Right " << std::endl;
    }
    else
    {
        x += Steps;
    }
}