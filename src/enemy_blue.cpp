#include "enemy_blue.h"

EnemyBlue::EnemyBlue(int position_y_, int position_x_, int hp_, bool was_moved_) : Enemy(position_y_, position_x_, hp_, was_moved_)
{
}

void EnemyBlue::render()
{
    attron(COLOR_PAIR(3));
    attron(A_BOLD);
    mvprintw(position_y,    position_x-2,    ">");
    mvprintw(position_y,    position_x-1,    "{");
    mvprintw(position_y,    position_x,      "O");
    mvprintw(position_y,    position_x+1,    "}");
    mvprintw(position_y,    position_x+2,    "<");
    mvprintw(position_y+1,  position_x,      "-");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(3));

    mvprintw(0,0, "+");
}

void EnemyBlue::derender()
{
    mvprintw(position_y,    position_x-1,    " ");
    mvprintw(position_y,    position_x-2,    " ");
    mvprintw(position_y,    position_x,      " ");
    mvprintw(position_y,    position_x+1,    " ");
    mvprintw(position_y,    position_x+2,    " ");
    mvprintw(position_y+1,  position_x,      " ");

    mvprintw(0,0, "+");
}

bool EnemyBlue::isShooting()
{
    return false;
}

std::vector<Bullet*> EnemyBlue::shoot()
{
    //return NULL;
}

bool EnemyBlue::move()
{
    if (++position_y < 58)
        return true;

    return false;
}

bool EnemyBlue::isMoving()
{
    int random = (std::rand() % 100);

    if(random < 2)
    {
        was_moved = true;
        return true;
    }

    return false;
}

void EnemyBlue::printToFile(std::ofstream &file)
{
    Shuttle::printToFile(file);
    file << "enemy_blue\n";
}

