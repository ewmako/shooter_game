#ifndef WEAPON_ADVANCED_H
#define WEAPON_ADVANCED_H

#include "weapon.h"
#include "bullet_advanced_left.h"
#include "bullet_advanced_right.h"
#include "bullet_simple.h"

class WeaponAdvanced : public Weapon
{
public:

    /**
     * @brief Weapon_advanced         Konstruktor klasy.
     */
    WeaponAdvanced();

    /**
     * @brief shoot                 Funkcja wystrzelająca pociski.
     * @param position_y_           Pozycja y początkowa pocisku.
     * @param position_x_           Pozycja x początkowa pocisku.
     */
    virtual std::vector<Bullet*> shoot(int position_y_, int position_x_, Bullet::Owner owner_);

    /**
     * @brief icon_display          Funkcja wyświetlająca nazwę broni.
     */
    virtual void icon_display();


    /**
     * @brief icon_remove           Funkcja usuwająca wyświetloną nazwę broni.
     */
    virtual void icon_remove();

    virtual void printToFile(std::ofstream &file);
};

#endif
