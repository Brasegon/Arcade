/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** testNcurses
*/

#include "IGraphLib.hpp"
#include "Ncurses.hpp"
#include <iomanip>

int main(void)
{
    IGraphLib *lib = new Ncurses();

    while (1) {
        if (lib->displayMenu() != 0)
            break;
    }
    delete lib;
}
// g++ Ncurses.cpp testNcurses.cpp -lncurses -o ncurses