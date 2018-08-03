#include "bullet.h"

Bullet::Bullet(int position_y_, int position_x_, Owner owner_)
{
    position_y = position_y_;
    position_x = position_x_;
    owner = owner_;
}

void Bullet::printToFile(std::ofstream &file)
{
    file << "Bullet\t" << position_y << '\t' << position_x << '\t';
    if (owner == Player)
        file << "player\t";
    else if (owner == Enemy)
        file << "enemy\t";
}
