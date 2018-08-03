#include "enemy_green.h"

EnemyGreen::EnemyGreen(int position_y_, int position_x_, int hp_, bool was_moved_) : Enemy(position_y_, position_x_, hp_, was_moved_)
{
    weapon = new WeaponSimple;
}

EnemyGreen::~EnemyGreen()
{
    delete weapon;
}

void EnemyGreen::render()
{
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
    mvprintw(position_y,    position_x-1,    "{");
    mvprintw(position_y,    position_x-2,    ">");
    mvprintw(position_y,    position_x,      "O");
    mvprintw(position_y,    position_x+1,    "}");
    mvprintw(position_y,    position_x+2,    "<");
    attroff(COLOR_PAIR(1));

    if(hp == 2)
    {
        attron(COLOR_PAIR(1));
        mvprintw(position_y+1,  position_x,      "=");
        attroff(COLOR_PAIR(1));
    }
    if(hp == 1)
    {
        attron(COLOR_PAIR(1));
        mvprintw(position_y+1,  position_x,      "-");
        attroff(COLOR_PAIR(1));
    }
    attroff(A_BOLD);

    mvprintw(0,0, "+");
}

void EnemyGreen::derender()
{
    mvprintw(position_y,    position_x-1,    " ");
    mvprintw(position_y,    position_x-2,    " ");
    mvprintw(position_y,    position_x,      " ");
    mvprintw(position_y,    position_x+1,    " ");
    mvprintw(position_y,    position_x+2,    " ");
    mvprintw(position_y+1,  position_x,      " ");
    mvprintw(0,0, "+");
}

bool EnemyGreen::isShooting()
{
    int random = (std::rand() % 100);

    if(random < 3)
        return true;

    return false;
}

std::vector<Bullet*> EnemyGreen::shoot()
{
    return weapon->shoot(position_y+2, position_x, Bullet::Enemy);
}

bool EnemyGreen::move()
{

}

bool EnemyGreen::isMoving()
{
    return false;
}

void EnemyGreen::printToFile(std::ofstream &file)
{
    Shuttle::printToFile(file);
    file << "enemy_green\n";
}
