#include "weapon_advanced.h"

WeaponAdvanced::WeaponAdvanced() : Weapon()
{
}

std::vector<Bullet*> WeaponAdvanced::shoot(int position_y_, int position_x_, Bullet::Owner owner_)
{
    std::vector<Bullet*> help;
    help.push_back(new BulletSimple(position_y_-2, position_x_, owner_));
    help.push_back(new BulletAdvancedLeft(position_y_-2, position_x_-1, owner_));
    help.push_back(new BulletAdvancedRight(position_y_-2, position_x_+1, owner_));
    return help;
}

void WeaponAdvanced::icon_display()
{
    mvprintw(icon_position_y,   icon_position_x,  "Advanced weapon");
}

void WeaponAdvanced::icon_remove()
{
    mvprintw(icon_position_y,   icon_position_x,  "               ");
}

void WeaponAdvanced::printToFile(std::ofstream &file)
{
    file << "weapon_advanced\n";
}
