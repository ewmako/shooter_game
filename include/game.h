#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <ncurses.h>
#include "bullet.h"
#include "enemy_blue.h"
#include "enemy_green.h"
#include "enemy_red.h"
#include "player.h"
#include "meteoroid.h"
#include "window.h"
#include "weapon.h"
#include "weapon_simple.h"
#include <vector>
#include <keyboard.h>
#include <assert.h>


class Game
{
public:
    /**
     * @brief Game              Konstruktor klasy.
     */
    Game();

    /**
     * @brief ~Game             Destruktor klasy.
     */
    ~Game();

    /**
     * @brief play              Funkcja odpowiadająca za zachowanie obiektów oraz interakcję z użytkownikiem podczas gry.
     * @return                  Zwraca fałsz gdy gra skończona.
     */
    bool play();

    /**
     * @brief over              Funkcja wywoływana przy zakończeniu gry, wyświetlająca statystyki.
     */
    void over();

private:

    /**
     * @brief createEnemies     Funkcja tworząca szyk wrogów.
     */
    void createEnemies();

    /**
     * @brief moveEnemy         Funkcja opisująca indywidualny ruch wroga.
     */
    bool moveEnemy();

    /**
     * @brief createMeteoroid   Funkcja tworząca meteoroid.
     */
    void createMeteoroid();

    /**
     * @brief moveMeteoroids    Funkcja odpowiedzialana za ruch meteoroidów.
     * @return                  Zwraca fałsz, gdy w wyniku zderzenia z meteoroidem ginie player.
     */
    bool moveMeteoroids();

    /**
     * @brief moveEnemies       Funkcja odpowiedzialna za cykliczny ruch wrogów na mapie.
     */
    void moveEnemies();

    /**
     * @brief shootEnemies      Wrogowie strzelają do gracza.
     */
    void shootEnemies();

    /**
     * @brief moveBulletSimples       Funkcja odpowiedzialna za ruch pocisków i zderzenia pocisków z wrogami i przeszkodami.
     */
    bool moveBullet();

    /**
     * @brief handleKeyboardInput   Funkcja odpowiadająca na dane wprowadzone przez użytkownika z klawiatury.
     * @return                      Zwraca fałsz przy wciśniętym klawiszu ESC.
     */
    bool handleKeyboardInput();

    void saveState();
    void cleanUp();
    void loadState();

    /**
     * @brief enemy             Wektor wskaźników na obiekty klasy enemy.
     */
    std::vector<Enemy*> enemy;

    /**
     * @brief player            Wskaźnik na obiekt typu player.
     */
    Player *player;

    /**
     * @brief bulletsimple            Wektor wskaźników na obiekty klasy bulletsimple.
     */
    std::vector<Bullet*> bullet;

    /**
     * @brief meteoroid         Wektor wskaźników na obiekty klasy meteoroid.
     */
    std::vector<Meteoroid*> meteoroid;

    /**
     * @brief keyboard          Wektor na obiekt typu keyboard.
     */
    Keyboard *keyboard;

    /**
     * @brief window            Wektor na obiekt typu window.
     */
    Window *window;

    /**
     * @brief cycle             Etap cyklu ruchu wrogów. Pełen cykl to 24 akcje.
     */
    int cycle;

    /**
     * @brief score             Liczba zdobytych punktów.
     */
    int score;

    int destroyed_enemies;

    int destroyed_meteoroids;

};

#endif
