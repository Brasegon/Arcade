/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** testNcurses
*/

#include "../IGraphLib.hpp"
#include "Ncurses.hpp"
#include <iomanip>

int main(void)
{
    IGraphLib *lib = new Ncurses();
    vector<string> gamelist;
    vector<string> liblist;
    gamelist.push_back("jeux1");
    gamelist.push_back("jeux2");
    gamelist.push_back("jeux3");
    liblist.push_back("lib1");
    liblist.push_back("lib2");
    liblist.push_back("lib3");
    lib->setGameList(gamelist);
    lib->setLibList(liblist);
    while (1) {
        if (lib->displayMenu() != 0)
            break;
    }
    delete lib;
}
// g++ Ncurses.cpp testNcurses.cpp -lncurses -o ncurses