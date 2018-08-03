#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>

#define KEYBOARD_DEV "/dev/input/event4"

struct keyboard_state
{
    signed short keys[KEY_CNT];
};

class Keyboard
{
  private:
    pthread_t thread;
    bool active;
    int keyboard_fd;
    input_event *keyboard_ev;
    keyboard_state *keyboard_st;
    char name[256];

  protected:
  public:
    Keyboard();
    ~Keyboard();
    bool init();
    static void* loop(void* obj);
    void readEv();
    short getKeyState(short key);
};

#endif // KEYBOARD_H
