#ifndef ENEMY_H
#define ENEMY_H

#include "shuttle.h"

/**
 * @brief Klasa bazowa obiektów będących statkami wroga.
 */
class Enemy : public Shuttle
{
protected:

    bool was_moved;

public:

    /**
     * @brief Enemy             Konstruktor klasy.
     * @param position_y_       Pozycja y statku.
     * @param position_x_       Pozycja x statku.
     * @param hp_               Wartość hp.
     */
    Enemy(int position_y_, int position_x_, int hp_, bool was_moved_);

    /**
     * @brief render            Wirtualna funkcja renderująca obiekt.
     */
    virtual void render() = 0;

    /**
     * @brief derender          Wirtualna funkcja derenderująca obiekt.
     */
    virtual void derender() = 0;

    /**
     * @brief shoot             Wirtualna funkcja umożliwiająca wrogom strzelanie.
     * @return                  Zwraca wskaźnik na pocisk wygenerowany przez broń wroga.
     */
    virtual std::vector<Bullet*> shoot() = 0;

    /**
     * @brief isShooting        Wirtualna funkcja sprawdzająca, czy dany wróg będzie strzelał.
     * @return                  Zwraca prawdę jeżeli dany wróg będzie strzelał.
     */
    virtual bool isShooting() = 0;

    /**
     * @brief appear            Funkcja losująca
     *                          czy w cyklu pojawi się szyk statków wroga.
     * @return
     */
    static bool appear();

    /**
     * @brief horizontalMove    Funkcja zmieniająca położenie wszystkich statków wroga.
     * @param move              Ilość przesunięć wykonanych w danym cyklu.
     */
    void horizontalMove(int move);

    /**
     * @brief isHere            Funkcja sprawdzająca czy statek zajmuje wskazaną pozycję.
     * @param y                 Pozycja y sprawdzana.
     * @param x                 Pozycja x sprawdzana.
     * @return                  Zwraca prawdę gdy statek wroga zajmuje pozycję.
     */
    bool isHere(int y, int x);

    virtual bool move() = 0;

    virtual bool isMoving() = 0;

    bool inline wasMoved()
    {
        return was_moved;
    }

};
#endif //ENEMY_H
