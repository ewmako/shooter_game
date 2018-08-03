#include "enemy_red.h"

EnemyRed::EnemyRed(int position_y_, int position_x_, int hp_, bool was_moved_) : Enemy(position_y_, position_x_, hp_, was_moved_)
{
}

void EnemyRed::render()
{
    attron(COLOR_PAIR(2));
    attron(A_BOLD);
    mvprintw(position_y,    position_x-2,    ">");
    mvprintw(position_y,    position_x-1,    "{");
    mvprintw(position_y,    position_x,      "O");
    mvprintw(position_y,    position_x+1,    "}");
    mvprintw(position_y,    position_x+2,    "<");
    mvprintw(position_y+1,  position_x,      "-");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(2));

    mvprintw(0,0, "+");
}

void EnemyRed::derender()
{
    mvprintw(position_y,    position_x-1,    " ");
    mvprintw(position_y,    position_x-2,    " ");
    mvprintw(position_y,    position_x,      " ");
    mvprintw(position_y,    position_x+1,    " ");
    mvprintw(position_y,    position_x+2,    " ");
    mvprintw(position_y+1,  position_x,      " ");
    mvprintw(0,0, "+");
}

std::vector<Bullet*> EnemyRed::shoot()
{
    //return NULL;
}

bool EnemyRed::isShooting()
{
    return false;
}

bool EnemyRed::move()
{

}

bool EnemyRed::isMoving()
{
    return false;
}

void EnemyRed::printToFile(std::ofstream &file)
{
    Shuttle::printToFile(file);
    file << "enemy_red\n";
}
