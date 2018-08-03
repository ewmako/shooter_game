#include <iostream>
#include <ncurses.h>
#include "game.h"

//Linux & timers
#include <sys/timerfd.h>
#include <unistd.h>

using namespace std;

//struktura przechowujaca inf o timer
struct periodic_info
{
    int timer_fd;
    unsigned long long wakeups_missed;
};

//funkcja ustawiajaca timer w tryb periodyczny
static int make_periodic (unsigned int period, struct periodic_info *info)
{
    int ret;
    unsigned int ns;
    unsigned int sec;
    int fd;
    struct itimerspec itval;

    //stworzenie timera
    fd = timerfd_create (CLOCK_MONOTONIC, 0);
    info->wakeups_missed = 0;
    info->timer_fd = fd;
    if (fd == -1)
        return fd;

    //ustawienie timer'a w tryb periodyczny
    sec = period/1000000;
    ns = (period - (sec * 1000000)) * 1000;
    itval.it_interval.tv_sec = sec;
    itval.it_interval.tv_nsec = ns;
    itval.it_value.tv_sec = sec;
    itval.it_value.tv_nsec = ns;
    ret = timerfd_settime (fd, 0, &itval, NULL);
    return ret;
}

//funkcja czekajaca
static void wait_period (struct periodic_info *info)
{
    unsigned long long missed;
    int ret;

    //poczekanie do pierwszego eventu / odczytanie liczby eventow
    ret = read (info->timer_fd, &missed, sizeof (missed));
    if (ret == -1)
    {
        perror ("read timer");
        return;
    }
}

int main()
{
    // Timer
    struct periodic_info info;
    make_periodic (200000, &info);

    // Game
    Game *game;
    try
    {
        game = new Game;
    }
    catch(const char* message)
    {
        std::cout << message << std::endl;
        std::exit(-1);
    }

    while (1)
    {
        // Game!
        if (!game->play())
        {
            // Game over
            game->over();
            break;
        }

        // Wait
        wait_period (&info);
    }

    return 0;
}
