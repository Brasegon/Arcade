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
#include <iostream>
#include <fstream>

class Ncurses : public IGraphLib
{
    public:
        Ncurses();
        ~Ncurses();
        void setGameList(vector<string>);
        void setLibList(vector<string>);
        void init_menu();
        void init_game();
        playerEvent displayMenu();
        void displayMap(map_info_t map);
        playerEvent getKey();
    protected:
    private:
        void update_scr();
        void save_score();
        menu_e menu;
        WINDOW *wmenu;
        WINDOW *wvisual;
        vector<string> gamelist;
        vector<string> liblist;
        char name[30];
};

#endif /* !NCURSES_HPP_ */
