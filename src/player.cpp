#include "player.h"

Player::Player(int position_y_, int position_x_, int hp_) : Shuttle(position_y_, position_x_, hp_)
{
    weapon = new WeaponSimple;
}

Player::~Player()
{
    delete weapon;
}

void Player::moveLeft()
{
    if(position_x > 5)
    position_x--;
}

void Player::moveRight()
{
    if(position_x < 174)
    position_x++;
}

void Player::render()
{
    attron(A_BOLD);
    attron(COLOR_PAIR(2));
    mvprintw(position_y-1,  position_x,     "^");
    mvprintw(position_y,    position_x-1,   "/");
    mvprintw(position_y,    position_x-2,   "/");
    mvprintw(position_y,    position_x+1,   "\\");
    mvprintw(position_y,    position_x+2,   "\\");
    mvprintw(position_y+1,  position_x-1,   "X");
    mvprintw(position_y+1,  position_x+1,   "X");
    attroff(COLOR_PAIR(2));

    mvprintw(position_y,    position_x,     "T");
    attroff(A_BOLD);

    weapon->icon_display();
    move(0,0);                  //karetka do (0,0)
}

void Player::derender()
{
    mvprintw(position_y-1,  position_x,     " ");
    mvprintw(position_y,    position_x-1,   " ");
    mvprintw(position_y,    position_x-2,   " ");
    mvprintw(position_y,    position_x+1,   " ");
    mvprintw(position_y,    position_x+2,   " ");
    mvprintw(position_y+1,  position_x-1,   " ");
    mvprintw(position_y+1,  position_x+1,   " ");
    mvprintw(position_y,    position_x,     " ");
    weapon->icon_remove();
}

std::vector<Bullet*> Player::shoot()
{
    return weapon->shoot(position_y, position_x, Bullet::Player);
}

void Player::changeWeaponSimple()
{
    delete weapon;
    weapon = new WeaponSimple;
}

void Player::changeWeaponAdvanced()
{
    delete weapon;
    weapon = new WeaponAdvanced;
}

void Player::printToFile(std::ofstream &file)
{
    Shuttle::printToFile(file);
    file << "player\t";
    weapon->printToFile(file);
}


