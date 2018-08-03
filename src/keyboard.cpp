#include <keyboard.h>

Keyboard::Keyboard()
{
    active = true;
    keyboard_fd = 0;
    keyboard_ev = new input_event();
    keyboard_st = new keyboard_state();
}

Keyboard::~Keyboard()
{
    if (keyboard_fd > 0)
    {
        active = false;
        pthread_join(thread, 0);
        close(keyboard_fd);
    }
    delete keyboard_st;
    delete keyboard_ev;
    keyboard_fd = 0;
}

bool Keyboard::init()
{
    keyboard_fd = open(KEYBOARD_DEV, O_RDONLY | O_NONBLOCK);
    if (keyboard_fd > 0)
    {
        ioctl(keyboard_fd, EVIOCGNAME(256), name);
        std::cout << "   Name: " << name << std::endl;
        active = true;
        pthread_create(&thread, 0, &Keyboard::loop, this);
        return true;
    }

    return false;
}

void* Keyboard::loop(void *obj)
{
    while (reinterpret_cast<Keyboard *>(obj)->active) reinterpret_cast<Keyboard *>(obj)->readEv();
}

void Keyboard::readEv()
{
    int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
    if (bytes > 0)
    {
        if (keyboard_ev->type & EV_KEY)
            keyboard_st->keys[keyboard_ev->code] = keyboard_ev->value;
    }
}

short Keyboard::getKeyState(short key)
{
    return keyboard_st->keys[key];
}
