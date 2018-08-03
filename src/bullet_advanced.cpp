#include "bullet_advanced.h"

BulletAdvanced::BulletAdvanced(int position_y_, int position_x_, Owner owner_) : Bullet(position_y_, position_x_, owner_)
{
}

bool BulletAdvanced::move()
{
    if (owner == Enemy)
    {
        if (++position_y<59)
            return true;
        else
            return false;
    } else if (owner == Player)
    {
        if (--position_y>0)
            return true;
        else return false;
    }

    return false;
}

void BulletAdvanced::render()
{
    if (owner == Enemy)
    {
        attron(COLOR_PAIR(1));
        attron(A_BOLD);
    }

    mvprintw(position_y,    position_x,     "|");

    if (owner == Enemy)
    {
        attroff(COLOR_PAIR(1));
    }
    mvprintw(0,0, "+");
}

void BulletAdvanced::derender()
{
    mvprintw(position_y,    position_x,     " ");
    mvprintw(0,0, "+");
}
