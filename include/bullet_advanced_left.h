#ifndef BULLET_ADVANCED_LEFT_H
#define BULLET_ADVANCED_LEFT_H

#include <ncurses.h>
#include "bullet.h"

/**
 * @brief Klasa generująca pociski.
 */
class BulletAdvancedLeft : public Bullet
{
public:
    /**
     * @brief BulletAdvanced      Konstruktor klasy.
     * @param position_y_       Pozycja y początkowa.
     * @param position_x_       Pozycja x początkowa.
     */
    BulletAdvancedLeft(int position_y_, int position_x_, Owner owner_);

    /**
     * @brief moveY            Sprawdza czy możliwy jest ruch pocisku w osi y,
     *                          jeśli możliwy to zmniejsza wartość y o 1.
     * @return                  Zwraca prawdę jeżeli ruch jest możliwy.
     */
    virtual bool move();

    /**
     * @brief render            Funkcja renderująca obiekt.
     */
    virtual void render();

    /**
     * @brief derender          Funkcja derenderująca obiekt.
     */
    virtual void derender();

    virtual void printToFile(std::ofstream &file);
};

#endif
