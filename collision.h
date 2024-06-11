#pragma once

#include <SDL2/SDL.h>

bool Collison(SDL_Rect collider1, SDL_Rect collider2)
{
    int topleft1, topleft2;
    int bottomleft1, bottomleft2;
    int topright1, topright2;
    int bottomright1, bottomright2;

    topleft1 = collider1.x;
    topleft2 = collider2.x;

    topright1 = collider1.x + collider1.w;
    topright2 = collider2.x + collider2.w;

    bottomleft1 = collider1.y;
    bottomleft2 = collider2.y;

    bottomright1 = collider1.y + collider1.h;
    bottomright2 = collider2.y + collider2.h;

    if (bottomright1 <= bottomleft2)
        return false;

    if (bottomleft1 >= bottomright2)
        return false;

    if (topright1 <= topleft2)
        return false;

    if (topleft1 >= topright2)
        return false;

    return true;
}

bool CollisionDetect(SDL_Rect &PacMan, SDL_Rect Colliders[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (Collison(PacMan, Colliders[i])){
            std::cout << i << "th Collider Collided " << std::endl;
            return true;
        }
    }

    return false;
}