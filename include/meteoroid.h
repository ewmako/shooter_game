#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "bullet.h"
#include "shuttle.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Shuttle;
class Bullet;

/**
 * @brief Klasa generująca przeszkody w formie meteoroidów.
 */
class Meteoroid
{

private:

    /**
     * @brief position_y    Pozycja y meteoroidu.
     */
    int position_y;

    /**
     * @brief position_x    Pozycja x meteoroidu.
     */
    int position_x;

    /**
     * @brief direction     Kierunek ruchu,
     *                      przyjmujący jedną z dwóch wartości 1 lub -1.
     *                      Wartość jest jednocześnie przesunięciem.
     */
    int direction;

public:

    /**
     * @brief Meteoroid     Konstruktor klasy.
     * @param position_y_   Pozycja y początkowa.
     * @param position_x_   Pozycja x początkowa.
     */
    Meteoroid(int position_y_, int position_x_);

    /**
     * @brief render        Funkcja renderująca obiekt.
     */
    void render();

    /**
     * @brief derender      Funkcja derenderująca obiekt.
     */
    void derender();

    /**
     * @brief appear        Funkcja losująca
     *                      czy w cyklu pojawi się meteoroid.
     * @return
     */
    static bool appear();

    /**
     * @brief fly           Funkcja generująca ruch meteoroidu
     *                      w obu osiach.
     * @param max_height    Maksymalna, końcowa pozycja y.
     * @return              Zwraca prawdę gdy ruch jest możliwy.
     */
    bool fly(int max_height);

    /**
     * @brief collide       Funkcja sprawdzająca
     *                      czy doszło do kolizji statek- meteoroid.
     * @param shuttle       Referencja do obiektu klasy Shuttle.
     * @param bulletsimple  Referencja do obiektu klasy Meteoroid.
     * @return              Zwraca prawdę gdy kolizja nastąpiła.
     */
    friend bool collide(const Shuttle &shuttle, const Meteoroid &meteoroid);

    /**
     * @brief collide       Funkcja sprawdzająca
     *                      czy doszło do kolizji meteorid-pocisk.
     * @param shuttle       Referencja do obiektu klasy Meteroid.
     * @param bullet        Referencja do obiektu klasy Bullet.
     * @return              Zwraca prawdę gdy kolizja nastąpiła.
     */
    friend bool collide(const Meteoroid &meteoroid, const Bullet &bullet);

    void printToFile(std::ofstream &file);
};

#endif
