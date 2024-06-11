#include "collision.h"

const int Steps = 2;

void MoveUp(double &d, int &y, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = -90;
    y -= Steps;
    
    if (y < 0 || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Up " << std::endl;

        y += Steps;
    }
}

void MoveDown(double &d, int &y, int screenHeight, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = 90;
    y += Steps;
    if (y + PacMan.w > screenHeight || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Down " << std::endl;

        y -= Steps;
    }
}

void MoveLeft(double &d, int &x, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = 180;
    x -= Steps;
    if (x < 0 || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Left " << std::endl;

        x += Steps;
    }
}

void MoveRight(double &d, int &x, int screenWidth, SDL_Rect PacMan, SDL_Rect Colliders[])
{
    d = 0;
    x += Steps;
    if (x + PacMan.w > screenWidth || CollisionDetect(PacMan, Colliders, 5))
    {
        std::cout << "Can't Move Right " << std::endl;

        x -= Steps;
    }
}