#include "meteoroid.h"

Meteoroid::Meteoroid(int position_y_, int position_x_)
{
    position_y = position_y_;
    position_x = position_x_;
    if(position_x<90) direction = 1;
    else direction = -1;
}

void Meteoroid::render()
{
    attron(A_BOLD);
    mvprintw(position_y,  position_x,     "O");
    mvprintw(position_y+1,  position_x,   "+");
    mvprintw(position_y-1,  position_x,   "+");
    mvprintw(position_y,  position_x+1,   "+");
    mvprintw(position_y,  position_x-1,   "+");
    attroff(A_BOLD);

    move(0,0);
}

void Meteoroid::derender()
{
    mvprintw(position_y,  position_x,     " ");
    mvprintw(position_y+1,  position_x,   " ");
    mvprintw(position_y-1,  position_x,   " ");
    mvprintw(position_y,  position_x+1,   " ");
    mvprintw(position_y,  position_x-1,   " ");

    move(0,0);
}

bool Meteoroid::appear()
{
    int random = (std::rand() % 100);

    if(random < 5)
        return true;

    return false;
}

bool Meteoroid::fly(int max_height)
{
    if(position_y < max_height)
    {
        position_x += direction;
        position_y++;
        return true;
    }
    return false;
}

bool collide(const Shuttle &shuttle, const Meteoroid &meteoroid)
{
   if(&meteoroid != NULL && &shuttle != NULL)
   {
       if(std::abs(shuttle.position_y - meteoroid.position_y) <=2 && std::abs(shuttle.position_x - meteoroid.position_x) <= 2)
           return true;

        return false;
   }
   return false;
}

bool collide(const Meteoroid &meteoroid, const Bullet &bullet)
{
   if(&bullet != NULL && &meteoroid != NULL)
   {
       if(meteoroid.position_y == bullet.position_y && std::abs(meteoroid.position_x - bullet.position_x) <= 2 && bullet.owner == Bullet::Player)
           return true;

        return false;
   }
   return false;
}

void Meteoroid::printToFile(std::ofstream &file)
{
    file<< "Meteoroid\t" << position_y << '\t' << position_x << '\n';
}
