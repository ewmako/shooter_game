#include "enemy.h"


Enemy::Enemy(int position_y_, int position_x_, int hp_, bool was_moved_) : Shuttle(position_y_, position_x_, hp_)
{
    was_moved = was_moved_;
}

bool Enemy::appear()
{
    int random = (std::rand() % 100);

    if(random < 80)
        return true;

    return false;
}


void Enemy::horizontalMove(int move)
{
    if(move < 12) position_x = position_x + 1;
    else position_x = position_x - 1;
}

bool Enemy::isHere(int y, int x)
{
    if(y == position_y && x == position_x)
        return true;
    return false;
}


