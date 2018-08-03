#ifndef BULLET_H
#define BULLET_H

#include <ncurses.h>
#include <fstream>

class Shuttle;
class Meteoroid;

/**
 * @brief Klasa bazowa pocisków.
 */
class Bullet
{
public:

    /**
     *  @brief      Deklaracja nowego typu wyliczeniowego Owner, gdzie Player
     *              oznacza, że pocisk należy do gracza, za Enemy oznacza, że
     *              pocisk należy do wroga.
     */
    typedef enum
    {
        Player,
        Enemy
    } Owner;

    /**
     * @brief Bullet            Konstruktor klasy.
     * @param position_y_       Pozycja y początkowa.
     * @param position_x_       Pozycja x początkowa.
     */
    Bullet(int position_y_, int position_x_, Owner owner_);

    /**
     * @brief move              Sprawdza czy możliwy jest ruch pocisku, jeśli jest
     *                          możliwy to w zależności od właściciela dokonuje go
     *                          w odpowiednim kierunku.
     * @return                  Zwraca prawdę jeżeli ruch jest możliwy.
     */
    virtual bool move() = 0;

    /**
     * @brief render            Funkcja renderująca obiekt, jeżeli pocisk należy do
     *                          wroga, to wyświetl go na zielono.
     */
    virtual void render() = 0;

    /**
     * @brief derender          Funkcja derenderująca obiekt.
     */
    virtual void derender() = 0;

    /**
     * @brief collide       Funkcja sprawdzająca
     *                      czy doszło do kolizji statek- pocisk.
     * @param shuttle       Referencja do obiektu klasy Shuttle.
     * @param bullet        Referencja do obiektu klasy Bullet.
     * @return              Zwraca prawdę gdy kolizja nastąpiła.
     */
    friend bool collide(const Shuttle &shuttle, const Bullet &bullet);

    /**
     * @brief collide       Funkcja sprawdzająca
     *                      czy doszło do kolizji meteorid-pocisk.
     * @param shuttle       Referencja do obiektu klasy Meteroid.
     * @param bullet        Referencja do obiektu klasy Bullet.
     * @return              Zwraca prawdę gdy kolizja nastąpiła.
     */
    friend bool collide(const Meteoroid &meteoroid, const Bullet &bullet);

    Owner inline getOwner()
    {
        return owner;
    }

    virtual void printToFile(std::ofstream &file);

protected:

    /**
     * @brief position_y        Pozycja y pocisku.
     */
    int position_y;

    /**
     * @brief position_x        Pozycja x pocisku.
     */
    int position_x;

    /**
     * @brief direction
     */
    Owner owner;
};


#endif

