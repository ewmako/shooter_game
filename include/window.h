#ifndef WINDOW_H
#define WINDOW_H

#include <player.h>
#include <ncurses.h>
#include <fstream>

/**
 * @brief The Window class
 */
class Window
{
private:

    /**
     * @brief size_y    Wysokość okna.
     */
    int size_y;

    /**
     * @brief size_x    Szerokość okna.
     */
    int size_x;

public:

    /**
     * @brief Window    Konstruktor klasy.
     */
    Window();

    friend Weapon* whatWeapon(const Window &window, const Player &player);

    /**
     * @brief render    Funkcja renderująca okno.
     */
    void render();

    /**
     * @brief getWidth  Zwraca szerokość okna.
     * @return
     */
    int inline getWidth()
    {
        return size_x;
    }


    /**
     * @brief getHeight Zwraca wysokość okna.
     * @return
     */
    int inline getHeight()
    {
        return size_y;
    }

//    void printToFile(std::ofstream &file);
};

#endif
