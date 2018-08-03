#include "bullet_advanced_right.h"

BulletAdvancedRight::BulletAdvancedRight(int position_y_, int position_x_, Owner owner_) : Bullet(position_y_, position_x_, owner_)
{
}

bool BulletAdvancedRight::move()
{
    if (--position_y<59 && ++position_x<180)
        return true;
    else
        return false;
}

void BulletAdvancedRight::render()
{
    mvprintw(position_y,    position_x,     "/");

    mvprintw(0,0, "+");
}

void BulletAdvancedRight::derender()
{
    mvprintw(position_y,    position_x,     " ");
    mvprintw(0,0, "+");
}

void BulletAdvancedRight::printToFile(std::ofstream &file)
{
    Bullet::printToFile(file);
    file << "advanced_right\n";
}
