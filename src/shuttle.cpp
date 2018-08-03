#include "shuttle.h"

Shuttle::Shuttle(int position_y_, int position_x_, int hp_)
{
    position_y = position_y_;
    position_x = position_x_;
    hp = hp_;
    size_x = 2;
}

int Shuttle::getPositionX()
{
    return position_x;
}

int Shuttle::getPositionY()
{
    return position_y;
}

bool Shuttle::hit()
{
    hp--;
    return (!hp);
}

bool collide(const Shuttle &shuttle, const Bullet &bullet)
{
    if(&bullet != NULL && &shuttle != NULL)
    {
        if(shuttle.position_y == bullet.position_y && std::abs(shuttle.position_x - bullet.position_x) <= 2)
            return true;

        return false;
    }
   return true;
}

bool Shuttle::collide(const Shuttle &shuttle)
{
    if(&shuttle != NULL)
    {
        if(std::abs(shuttle.position_y - position_y)<=1 && std::abs(shuttle.position_x - position_x) <= 2)
            return true;

        return false;
    }
   return true;
}

void Shuttle::printToFile(std::ofstream &file)
{
    file<< "Shuttle\t" << position_y << '\t' << position_x << '\t' << hp << '\t';
}
