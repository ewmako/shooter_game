#ifndef SHUTTLE_H
#define SHUTTLE_H

#include <cmath>
#include <cstdlib>
#include "weapon.h"

class Meteoroid;

/**
 * @brief Klasa bazowa obiektów będących statkami kosmicznymi.
 */
class Shuttle
{
protected:

    /**
     * @brief position_y    Pozycja y statku.
     */
    int position_y;

    /**
     * @brief position_x    Pozycja x statku.
     */
    int position_x;

    /**
     * @brief hp            Wartość hp.
     */
    int hp;

    /**
     * @brief size_x        Szerokość skrzydła statku.
     */
    int size_x;

    /**
     * @brief weapon        Bron.
     */
    Weapon *weapon;

public:

    /**
     * @brief Shuttle       Konstruktor klasy.
     * @param position_y_   Pozycja y początkowa.
     * @param position_x_   Pozycja x początkowa.
     * @param hp_           Początkowa wartość hp.
     */
    Shuttle(int position_y_, int position_x_, int hp_);

    /**
     * @brief render        Wirtualna funkcja renderująca obiekt.
     */
    virtual void render() = 0;

    /**
     * @brief derender      Wirtualna funkcja derenderująca obiekt.
     */
    virtual void derender() = 0;

    /**
     * @brief shoot         Funkcja zwraca wskaźnik na pocisk.
     */
    virtual std::vector<Bullet*> shoot() = 0;

    /**
     * @brief collide       Funkcja sprawdzająca
     *                      czy doszło do kolizji statek- pocisk.
     * @param shuttle       Referencja do obiektu klasy Shuttle.
     * @param bulletsimple  Referencja do obiektu klasy BulletSimple.
     * @return              Zwraca prawdę gdy kolizja nastąpiła.
     */
    friend bool collide(const Shuttle &shuttle, const Bullet &bullet);

    /**
     * @brief collide       Funkcja sprawdzająca
     *                      czy doszło do kolizji statek- meteoroid.
     * @param shuttle       Referencja do obiektu klasy Shuttle.
     * @param bulletsimple        Referencja do obiektu klasy Meteoroid.
     * @return              Zwraca prawdę gdy kolizja nastąpiła.
     */
    friend bool collide(const Shuttle &shuttle, const Meteoroid &meteoroid);

    /**
     * @brief getPositionX  Funkcja zwracająca pozycję x statku.
     * @return
     */
    int getPositionX();

    /**
     * @brief getPositionY  Funkcja zwracająca pozycję y statku.
     * @return
     */
    int getPositionY();

    /**
     * @brief hit           Funkcja zmniejszająca wartość hp statku o 1.
     * @return              Zwraca prawdę gdy hp = 0.
     */
    bool hit();

    bool collide(const Shuttle &shuttle);

    virtual void printToFile(std::ofstream &file);
};

#endif //SHUTTLE_H
