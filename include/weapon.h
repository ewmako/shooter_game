#ifndef WEAPON_H
#define WEAPON_H

#include <ncurses.h>
#include <vector>
#include "bullet.h"

/**
 * @brief Klasa generująca pociski.
 */
class Weapon
{
protected:

    /**
     * @brief icon_position_y           Pozycja y wyświetlanej nazwy.
     */
    int icon_position_y;

    /**
     * @brief icon_position_x           Pozycja x wyświetlanej nazwy.
     */
    int icon_position_x;

public:

    /**
     * @brief Weapon                    Konstruktor klasy.
     */
    Weapon();

    /**
     * @brief shoot                     Wirtualna funkcja tworząca pociski.
     */
    virtual std::vector<Bullet*> shoot(int position_y_, int position_x_, Bullet::Owner owner_) = 0;

    /**
     * @brief icon_display              Wirtualna funkcja wyświetlająca nazwę typu broni.
     */
    virtual void icon_display() = 0;

    /**
     * @brief icon_remove               Wirtualna funkcja usuwająca nazwę typu broni.
     */
    virtual void icon_remove() = 0;

    virtual void printToFile(std::ofstream &file) = 0;
};

#endif
