#include "bullet_advanced_left.h"

BulletAdvancedLeft::BulletAdvancedLeft(int position_y_, int position_x_, Owner owner_) : Bullet(position_y_, position_x_, owner_)
{
}

bool BulletAdvancedLeft::move()
{
    if (--position_y<59 && --position_x>0)
        return true;
    else
        return false;
}

void BulletAdvancedLeft::render()
{
    mvprintw(position_y,    position_x,     "\\");
    mvprintw(0,0, "+");
}

void BulletAdvancedLeft::derender()
{
    mvprintw(position_y,    position_x,     " ");
    mvprintw(0,0, "+");
}

void BulletAdvancedLeft::printToFile(std::ofstream &file)
{
    Bullet::printToFile(file);
    file << "advanced_left\n";
}
