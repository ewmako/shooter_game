#ifndef ENEMYRED_H
#define ENEMYRED_H

#include "enemy.h"
#include <ncurses.h>

/**
 * @brief Klasa generująca czerwone statki wroga.
 */
class EnemyRed : public Enemy
{
public:

    /**
     * @brief EnemyRed      Konstruktor klasy.
     * @param position_y_   Pozycja y początkowa.
     * @param position_x_   Pozycja x początkowa.
     * @param hp_           Początkowe hp.
     */
    EnemyRed(int position_y_, int position_x_, int hp_, bool was_moved_);

    /**
     * @brief render        Funkcja renderująca obiekt.
     */
    virtual void render();

    /**
     * @brief derender      Funkcja derenderująca obiekt.
     */
    virtual void derender();

    /**
     * @brief shoot         Wirtualna funkcja umożliwiająca wrogom strzelanie.
     * @return              Nic nie jest zwracane, ponieważ niebieski wróg nie strzela.
     */
    virtual std::vector<Bullet*> shoot();

    /**
     * @brief isShooting    Wirtualna funkcja sprawdzająca, czy wróg będzie strzelał.
     * @return              Zwraca zawsze fałsz, ponieważ niebieski wróg nie strzela.
     */
    virtual bool isShooting();

    virtual bool move();

    virtual bool isMoving();

    virtual void printToFile(std::ofstream &file);
};

#endif //ENEMYRED_H
