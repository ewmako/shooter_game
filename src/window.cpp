#include "window.h"


Window::Window()
{
    size_y = 60;
    size_x = 180;
}


void Window::render()
{
    for(int x = 1; x < size_x; x++)
    {
        mvprintw(0, x,       "-");
        mvprintw(size_y, x,  "-");
    }

    for(int y = 1; y < size_y; y++)
    {
        mvprintw(y, 0,       "|");
        mvprintw(y, size_x,  "|");
    }

    mvprintw(0, 0,           "+");
    mvprintw(0, size_x,      "+");
    mvprintw(size_y, 0,      "+");
    mvprintw(size_y, size_x, "+");
}

//void Window::printToFile(std::ofstream &file)
//{
//    file << "Window\t" << size_x << '\t' << size_y << std::endl;
//}
