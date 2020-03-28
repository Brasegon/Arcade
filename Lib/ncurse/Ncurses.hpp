/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** Ncurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "../IGraphLib.hpp"
#include <ncurses.h>
#include <thread>

class Ncurses : public IGraphLib
{
    public:
        Ncurses();
        ~Ncurses();
        void setGameList(vector<string>);
        void setLibList(vector<string>);
        void init_menu();
        void init_game();
        int displayMenu();
        void displayMap(map_info_t map);
        int getKey();
    protected:
    private:
        void update_scr();
        menu_e menu;
        WINDOW *wmenu;
        WINDOW *wvisual;
        vector<string> gamelist;
        vector<string> liblist;
        char name[30];
};

#endif /* !NCURSES_HPP_ */
