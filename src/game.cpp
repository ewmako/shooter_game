#include "game.h"

Game::Game()
{
    // ustawienie klawiatury
    keyboard = new Keyboard();
    if (!keyboard->init())
        throw "Nie mozna ustawic klawiatury! Moze zabraklo sudo?";

    //random
    srand( time( NULL ) );

    //inicjowanie programu w trybie ncurses
    initscr();

    // update wygladu
    refresh();

    cycle = 0;

    score = 0;

    destroyed_enemies = 0;

    destroyed_meteoroids = 0;

    // Przydzielnaie pamięci obiektowi window
    window = new Window();

    // Przydzielanie pamięci obioektowi player
    player = new Player(window->getHeight()-5, window->getWidth()/2, 1);

    // Inicjalizacja kolorow
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}

Game::~Game()
{
    // Wyczysc
    cleanUp();

    // Zwalnianie zasobow klawiatury
    delete keyboard;

    // Koniec trybu ncurses
    endwin();
}

void Game::cleanUp()
{
    // Zwalnianie pamieci wektora wskaznikow enemy
    for (std::vector<Enemy*>::iterator enemy_it = enemy.begin();
         enemy_it!=enemy.end();)
    {
        (*enemy_it)->derender();
        delete *enemy_it;
        enemy_it = enemy.erase(enemy_it);
    }

    // Zwalnianie pamieci wektora wskaznikow meteoroid
    for (std::vector<Meteoroid*>::iterator meteroid_it = meteoroid.begin();
         meteroid_it!=meteoroid.end();)
    {
        (*meteroid_it)->derender();
        delete *meteroid_it;
        meteroid_it = meteoroid.erase(meteroid_it);
    }

    // Zwolnienie pamieci player
    player->derender();
    delete player;

    // Zwolnienie pamieci wektora wskaznikow bulletsimple
    for (std::vector<Bullet*>::iterator bullet_it = bullet.begin();
         bullet_it!=bullet.end();)
    {
        (*bullet_it)->derender();
        delete *bullet_it;
        bullet_it = bullet.erase(bullet_it);
    }
}

bool Game::play()
{
    // Render
    window->render();

    // Render
    player->render();

    // Wyswietlanie "a"
    static int czas = 0;
    mvprintw(czas++, window->getWidth(), "a");
    if (czas==window->getHeight()) czas=0;

    // Pojawianie sie meteoroidu, losowanie polozenia
    createMeteoroid();

    // Bujanie sie statkow wroga w poziomie
    moveEnemies();

    // Pojawianie sie szyku statkow wroga, losowanie polozenia
    createEnemies();

    // Wrogowie strzelają do gracza
    shootEnemies();

    //Indywidualny ruch statku wroga
    if(!moveEnemy()) return 0;

    // Ruch meteoridów
    if(!moveMeteoroids()) return 0;

    // Ruch pocisków
    if(!moveBullet()) return 0;

    // Reagowanie na wejscie klawiaturowe
    if(!handleKeyboardInput()) return 0;

    refresh();
    return true;
}

void Game::over()
{
    mvprintw((window->getHeight()/2)-4, (window->getWidth()/2)-4,   "GAME OVER!");
    mvprintw((window->getHeight()/2)-2, (window->getWidth()/2)-12,  "SCORE:                     %i", score);
    mvprintw((window->getHeight()/2), (window->getWidth()/2)-12,    "Destroyed enemies:         %i", destroyed_enemies);
    mvprintw((window->getHeight()/2)+2, (window->getWidth()/2)-12,  "Destroyed meteoroids:      %i", destroyed_meteoroids);
    mvprintw((window->getHeight()/2)+4, (window->getWidth()/2)-8,   "Press ENTER to exit");
    move(0,0);

    refresh();

    while (!keyboard->getKeyState(KEY_ENTER));
}

void Game::moveEnemies()
{
    for(int i=0; i<enemy.size(); i++)
    {
        enemy.at(i)->derender();
        enemy.at(i)->horizontalMove(cycle);
        enemy.at(i)->render();
    }

    // Cykl to 24 przesuniecia, przejście do następnego etapu.
    if(++cycle == 24) cycle = 0;
}

void Game::createEnemies()
{
    if (Enemy::appear() && cycle % 8 == 0)
    {
        int y = ((std::rand() % 4)*4 + 9);
        int x = ((std::rand() % 16)*8 + 30);

        bool is_empty = true;

        // Sprawdzanie zajetosci pozycji
        for(int i = 0; i<enemy.size(); i++)
            if (enemy.at(i)->isHere(y,x) || enemy.at(i)->isHere(y,x-8) || enemy.at(i)->isHere(y,x+8))
            {
                is_empty = false;
                break;
            }

        if (is_empty)
        {
            //Losowanie typu wroga
            int type = (std::rand() % 3);

            if(type == 0)
            {
                // Tworzenie i dodawanie na koncu tab enemy, render
                enemy.push_back(new EnemyGreen(y,x-8,2,false));
                enemy.at(enemy.size()-1)->render();
                enemy.push_back(new EnemyGreen(y,x,2,false));
                enemy.at(enemy.size()-1)->render();
                enemy.push_back(new EnemyGreen(y,x+8,2,false));
                enemy.at(enemy.size()-1)->render();
            }
            else if (type == 1)
            {
                enemy.push_back(new EnemyRed(y,x-8,1,false));
                enemy.at(enemy.size()-1)->render();
                enemy.push_back(new EnemyRed(y,x,1,false));
                enemy.at(enemy.size()-1)->render();
                enemy.push_back(new EnemyRed(y,x+8,1,false));
                enemy.at(enemy.size()-1)->render();
            }
            else if (type == 2)
            {
                enemy.push_back(new EnemyBlue(y,x-8,1,false));
                enemy.at(enemy.size()-1)->render();
                enemy.push_back(new EnemyBlue(y,x,1,false));
                enemy.at(enemy.size()-1)->render();
                enemy.push_back(new EnemyBlue(y,x+8,1,false));
                enemy.at(enemy.size()-1)->render();
            }
        }
    }
}

bool Game::moveEnemy()
{
    for(std::vector<Enemy*>::iterator enemy_it = enemy.begin();
        enemy_it != enemy.end(); )
    {
        //Ruch indywidualny ruch wroga, jeśli dozwolony
        if ((*enemy_it)->isMoving() || (*enemy_it)->wasMoved())
        {
            (*enemy_it)->derender();

            if((*enemy_it)->move())
            {
                // Gdy kolizja z playerem
                if (player->collide(**enemy_it))
                {
                    // Zwolnienie pamieci
                    delete *enemy_it;

                    // Usuwanie ob z wektora
                    enemy_it = enemy.erase(enemy_it);

                    // Derender
                    player->derender();

                    // Jesli player zestrzelony
                    if (player->hit())
                    {
                        return false;
                    }
                    else
                    {
                        // player render
                        player->render();
                    }
                }
                else
                {
                    //Nie nastapila kolizja, enemy render
                        (*enemy_it)->render();
                        ++enemy_it;
                }
            } else
            {
                // Zwolnienie pamieci
                delete *enemy_it;

                // Usuwanie ob z wektora
                enemy_it = enemy.erase(enemy_it);
            }
        } else ++enemy_it;
    }
    return true;
}

void Game::shootEnemies()
{
    for(int i=0; i<enemy.size(); i++)
    {
        if (enemy.at(i)->isShooting())
        {
            std::vector<Bullet*> help = (enemy.at(i)->shoot());
            for(int i=0; i<help.size(); i++)
                help.at(i)->render();
            bullet.insert(bullet.end(), help.begin(), help.end());
        }
    }
}

void Game::createMeteoroid()
{
    if (Meteoroid::appear())
    {
        int y, x;
        y = (std::rand() % 25 + 25);
        x = (std::rand() % 170 + 5);

        // Tworzenie obiektu, render
        meteoroid.push_back(new Meteoroid(y,x));
        meteoroid.at(meteoroid.size()-1)->render();
    }
}

bool Game::moveMeteoroids()
{
    for(std::vector<Meteoroid*>::iterator meteoroid_it = meteoroid.begin();
        meteoroid_it != meteoroid.end(); )
    {
        (*meteoroid_it)->derender();

        // Ruch meteorytu po y, jesli pozycja miesci sie w oknie, render
        if((*meteoroid_it)->fly(window->getHeight()-2))
        {
            bool collided = false;

            for(std::vector<Enemy*>::iterator enemy_it = enemy.begin();
                enemy_it != enemy.end(); )
            {
                // Gdy kolizja
                if (collide(**enemy_it, **meteoroid_it))
                {
                    collided = true;

                    // Zwolnienie pamieci
                    delete *meteoroid_it;

                    // Usuwanie obiektu z wektora pamieci
                    meteoroid_it = meteoroid.erase(meteoroid_it);

                    // Jesli wrog zestrzelony
                    if ((*enemy_it)->hit())
                    {
                        // Derender
                        (*enemy_it)->derender();

                        // Zwolnienie pamieci
                        delete *enemy_it;

                        // Usuwanie ob z wektora
                        enemy_it = enemy.erase(enemy_it);
                    }
                    else
                    {
                        // Wrog przezyl, wrog render
                        (*enemy_it)->render();
                        ++enemy_it;
                    }
                } else ++enemy_it;
            }

            if(!collided)
            {
                // Gdy kolizja z playerem
                if (collide(*player, **meteoroid_it))
                {
                    // Zwolnienie pamieci
                    delete *meteoroid_it;

                    // Usuwanie ob z wektora
                    meteoroid_it = meteoroid.erase(meteoroid_it);

                    // Derender
                    player->derender();

                    // Jesli player zestrzelony
                    if (player->hit())
                    {
                        return false;
                    }
                    else
                    {
                        // player render
                        player->render();
                    }
                }
                else
                {
                    //Nie nastapila kolizja, meteoroid render
                    (*meteoroid_it)->render();
                    ++meteoroid_it;
                }
            }
        }
        else
        {
            // Zwolnienie pamieci
            delete *meteoroid_it;

            // Usuwanie ob z wektora
            meteoroid_it = meteoroid.erase(meteoroid_it);
        }
    }

    return true;
}

bool Game::moveBullet()
{
    for(std::vector<Bullet*>::iterator bullet_it = bullet.begin();
        bullet_it != bullet.end(); )
    {
        // Derender
        (*bullet_it)->derender();

        // Ruch pocisku po y
        if((*bullet_it)->move())
        {
            bool collided = false;

            for(std::vector<Meteoroid*>::iterator meteoroid_it = meteoroid.begin();
                meteoroid_it != meteoroid.end(); )
            {
                if (collide(**meteoroid_it, **bullet_it) && (*bullet_it)->getOwner() == Bullet::Player)
                {
                    // Score
                    score = score + 5;
                    destroyed_meteoroids++;
                    collided = true;

                    // Zwolnienie pamieci
                    delete *bullet_it;

                    // Usuwanie obiektu z wektora pamieci
                    bullet_it = bullet.erase(bullet_it);

                    // Derender
                    (*meteoroid_it)->derender();

                    // Zwolnienie pamieci
                    delete *meteoroid_it;

                    // Usuwanie obiektu z wektora pamieci
                    meteoroid_it = meteoroid.erase(meteoroid_it);
                } else ++meteoroid_it;
            }

            if(!collided)
            {
                for(std::vector<Enemy*>::iterator enemy_it = enemy.begin();
                    enemy_it != enemy.end(); )
                {
                    // Gdy kolizja
                    if (collide(**enemy_it, **bullet_it) && (*bullet_it)->getOwner() == Bullet::Player)
                    {
                        //Score
                        score++;
                        collided = true;

                        // Zwolnienie pamieci
                        delete *bullet_it;

                        // Usuwanie obiektu z wektora pamieci
                        bullet_it = bullet.erase(bullet_it);

                        // Jesli wrog zestrzelony
                        if ((*enemy_it)->hit())
                        {
                            destroyed_enemies++;
                            // Derender
                            (*enemy_it)->derender();

                            // Zwolnienie pamieci
                            delete *enemy_it;

                            // Usuwanie ob z wektora
                            enemy_it = enemy.erase(enemy_it);
                        }
                        else
                        {
                            // Wrog przezyl, wrog render
                            (*enemy_it)->render();
                            ++enemy_it;
                        }
                    } else ++enemy_it;
                }
            }

            if(!collided)
            {
                // Gdy kolizja z graczem
                if (collide(*player, **bullet_it) && (*bullet_it)->getOwner() == Bullet::Enemy)
                {
                    collided = true;

                    // Zwolnienie pamieci
                    delete *bullet_it;

                    // Usuwanie obiektu z wektora pamieci
                    bullet_it = bullet.erase(bullet_it);

                    // Derender
                    player->derender();

                    // Jesli player zestrzelony
                    if (player->hit())
                    {
                        return false;
                    }
                    else
                    {
                        // player render
                        player->render();
                    }
                }
            }

            // Nie ma kolizji, bulletsimple render, idz do kolejnego elementu
            if (!collided)
            {
                (*bullet_it)->render();
                ++bullet_it;
            }
        }
        else
        {
            // Zwolnienie pamieci
            delete *bullet_it;

            // Usuwanie obiektu z wektora pamieci
            bullet_it = bullet.erase(bullet_it);
        }
    }
    return true;
}

bool Game::handleKeyboardInput()
{
    if (keyboard->getKeyState(KEY_LEFT))
    {
        player->derender();
        player->moveLeft();
        player->render();
    }
    if (keyboard->getKeyState(KEY_RIGHT))
    {
        player->derender();
        player->moveRight();
        player->render();
    }
    if (keyboard->getKeyState(KEY_SPACE))
    {
        std::vector<Bullet*> help = (player->shoot());
        for(int i=0; i<help.size(); i++)
            help.at(i)->render();
        bullet.insert(bullet.end(), help.begin(), help.end());
    }
    if (keyboard->getKeyState(KEY_1)) player->changeWeaponSimple();
    if (keyboard->getKeyState(KEY_2)) player->changeWeaponAdvanced();
    if (keyboard->getKeyState(KEY_S)) saveState();
    if (keyboard->getKeyState(KEY_L)) loadState();
    if (keyboard->getKeyState(KEY_ESC)) return 0;

    return 1;
}

void Game::saveState()
{
    std::ofstream file ("state.txt");
    if (file.is_open())
    {
        player->printToFile(file);

        file << "ENEMIES\t" << enemy.size() << std::endl;
        for (int i = 0; i < enemy.size(); i++)
            enemy.at(i)->printToFile(file);

        file << "BULLETS\t" << bullet.size() << std::endl;
        for (int i = 0; i < bullet.size(); i++)
            bullet.at(i)->printToFile(file);

        file << "METEOROIDS\t" << meteoroid.size() << std::endl;
        for (int i = 0; i < meteoroid.size(); i++)
            meteoroid.at(i)->printToFile(file);

        file << "Game\t" << score << '\t' << destroyed_enemies << '\t' << destroyed_meteoroids << '\t' << cycle;

        file.close();
    } else std::cout << "NIE MA PLIKU";
}

void Game::loadState()
{
    //Wyczysc obecny stan
    cleanUp();

    //Otworz plik
    std::ifstream file ("state.txt");
    if (file.is_open())
    {
        // Zmienne pomocnicze
        std::string temp, type, weapon;
        int pos_y, pos_x, hp, count;

        // Wczytaj dane gracza
        file >> temp >> pos_y >> pos_x >> hp >> type >> weapon;

        player = new Player(pos_y, pos_x, hp);
        if (weapon=="weapon_simple")
            player->changeWeaponSimple();
        else if (weapon=="weapon_advanced")
            player->changeWeaponAdvanced();
        player->render();

        // Wczytaj dane przeciwnikow
        file >> temp >> count;
        for (int i=0; i<count; i++)
        {
            file >> temp >> pos_y >> pos_x >> hp >> type;

            if (type == "enemy_red")
                enemy.push_back(new EnemyRed(pos_y, pos_x, 1, false));
            else if (type == "enemy_green")
                enemy.push_back(new EnemyGreen(pos_y, pos_x, 2, false));
            else if (type == "enemy_blue")
                enemy.push_back(new EnemyBlue(pos_y, pos_x, 1, false));
            else assert(false);
            enemy.at(enemy.size()-1)->render();
        }

        // Wczytaj dane pociskow
        file >> temp >> count;
        for (int i=0; i<count; i++)
        {
            file >> temp >> pos_y >> pos_x >> type >> weapon;

            Bullet::Owner owner;
            if (type == "player")
                owner = Bullet::Player;
            else if (type == "enemy")
                owner = Bullet::Enemy;
            else assert(false);

            if (weapon == "simple")
                bullet.push_back(new BulletSimple(pos_y, pos_x, owner));
            else if (weapon == "advanced_left")
                bullet.push_back(new BulletAdvancedLeft(pos_y, pos_x, owner));
            else if (weapon == "advanced_right")
                bullet.push_back(new BulletAdvancedRight(pos_y, pos_x, owner));
            bullet.at(bullet.size()-1)->render();
        }

        // Wczytaj dane meteoroidow
        file >> temp >> count;
        for (int i=0; i<count; i++)
        {
            file >> temp >> pos_y >> pos_x;

            meteoroid.push_back(new Meteoroid(pos_y, pos_x));
            meteoroid.at(meteoroid.size()-1)->render();
        }

        // Wczytaj dane gry
        int a, b, c, d;
        file >> temp >> a >> b >> c >> d;

        score = a;
        destroyed_enemies = b;
        destroyed_meteoroids = c;
        cycle = d;
    }

    refresh();
}
