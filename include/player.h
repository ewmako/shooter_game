#ifndef PLAYER_H
#define PLAYER_H

#include "shuttle.h"
#include "weapon_simple.h"
#include "weapon_advanced.h"
#include <ncurses.h>

class BulletSimple;

/**
 * @brief Klasa generująca statek gracza.
 */
class Player : public Shuttle
{
public:
    /**
     * @brief Player        Konstruktor klasy.
     * @param position_y_   Pozycja y początkowa.
     * @param position_x_   Pozycja x początkowa.
     * @param hp_           Początkowa wartość hp.
     * @param shield_       Początkowa osłona.
     */
    Player(int position_y_, int position_x_, int hp_);

    ~Player();

    /**
     * @brief moveLeft      Funkcja zmieniająca pozycję x o 1 w lewo.
     */
    void moveLeft();

    /**
     * @brief moveRight     Funkcja zmieniająca pozycję x o 1 w prawo.
     */
    void moveRight();

    /**
     * @brief render        Funkcja renderująca obiekt.
     */
    virtual void render();

    /**
     * @brief derender      Funkcja derenderująca obiekt.
     */
    virtual void derender();

    /**
     * @brief shoot         Metoda generująca pocisk z pozycją gracza oraz
     *                      oznaczająca, że ten pocisk należy do gracza.
     * @return              Wskaźnik na pocisk wygenerowany przez broń.
     */
    virtual std::vector<Bullet*> shoot();

    void changeWeaponSimple();

    void changeWeaponAdvanced();

    virtual void printToFile(std::ofstream &file);
};

#endif //PLAYER_H
