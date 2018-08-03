#ifndef ENEMYGREEN_H
#define ENEMYGREEN_H

#include <ncurses.h>
#include "enemy.h"
#include "weapon_simple.h"

/**
 * @brief Klasa generujaca zielone statki wroga.
 */
class EnemyGreen : public Enemy
{
public:

    /**
     * @brief EnemyGreen    Konstruktor klasy.
     * @param position_y_   Pozycja y początkowa.
     * @param position_x_   Pozycja x początkowa.
     * @param hp_           Początkowe hp.
     */
    EnemyGreen(int position_y_, int position_x_, int hp_, bool was_moved_);

    ~EnemyGreen();

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
     * @return              Zwraca wskaźnik na pocisk wygenerowany przez broń wroga.
     */
    virtual std::vector<Bullet*> shoot();

    /**
     * @brief isShooting        Wirtualna funkcja sprawdzająca, czy dany wróg będzie strzelał.
     * @return                  Zwraca prawdę jeżeli wróg będzie strzelał.
     */
    virtual bool isShooting();

    virtual bool move();

    virtual bool isMoving();

    virtual void printToFile(std::ofstream &file);
};

#endif //ENEMYGREEN_H
