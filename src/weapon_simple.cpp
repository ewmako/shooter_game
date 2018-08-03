#include "weapon_simple.h"

WeaponSimple::WeaponSimple() : Weapon()
{
}

std::vector<Bullet*> WeaponSimple::shoot(int position_y_, int position_x_, Bullet::Owner owner_)
{
    std::vector<Bullet*> help;
    help.push_back(new BulletSimple(position_y_-2, position_x_, owner_));
    return help;
}

void WeaponSimple::icon_display()
{
    mvprintw(icon_position_y,   icon_position_x,  "Simple weapon");
}

void WeaponSimple::icon_remove()
{
    mvprintw(icon_position_y,   icon_position_x,  "             ");
}

void WeaponSimple::printToFile(std::ofstream &file)
{
    file << "weapon_simple\n";
}
