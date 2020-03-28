/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** testNcurses
*/

#include "../IGraphLib.hpp"
#include "Ncurses.hpp"
#include <iomanip>

void game_loop(IGraphLib *lib);

void menu_loop(IGraphLib *lib)
{
    int ret;
    lib->init_menu();
    while (1) {
        ret = lib->displayMenu();
        if (ret == -1)
            return;
        if (ret == 1) {
            game_loop(lib);
            return;
        }
    }
}

void game_loop(IGraphLib *lib)
{
    int ret;
    map_info_t mapinfo;
    vector<string> map;
    map.push_back("------------------------");
    map.push_back("|test ligne 2 de la map|");
    map.push_back("|test ligne 3 de la map|");
    map.push_back("|test ligne 4 de la map|");
    map.push_back("------------------------");
    mapinfo.map = map;
    lib->init_game();
    while (1) {
        /*ICI RECUP MAP DEPUIS LE JEU*/
        lib->displayMap(mapinfo);
        ret = lib->getKey();
        if (ret == 'q')
            return;
        if (ret == 'm') {
            menu_loop(lib);
            return;
        }
    }
}

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
    menu_loop(lib);
    delete lib;
}
// g++ Ncurses.cpp testNcurses.cpp -lncurses -o ncurses