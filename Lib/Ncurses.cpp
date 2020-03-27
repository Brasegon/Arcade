/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
    menu = GAMES;
    name[0] = 'p';
    name[1] = 'l';
    name[2] = 'a';
    name[3] = 'y';
    name[4] = 'e';
    name[5] = 'r';
    name[6] = '\0';
    gamelist.push_back("jeux1");
    gamelist.push_back("jeux2");
    gamelist.push_back("jeux3");
    liblist.push_back("lib1");
    liblist.push_back("lib2");
    liblist.push_back("lib3");
    /*-- initialisation stdscr --*/
    initscr();
    curs_set(0);
    noecho();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    refresh();
    /*-- initialisation wmenu --*/
    wmenu = newwin(LINES, COLS/4, 0, 0);
    box(wmenu, 0, 0);
    wmove(wmenu, 1, 2);
    waddstr(wmenu, "GAMES");
    wmove(wmenu, 2, 2);
    waddstr(wmenu, "GRAPHICAL LIBRARY");
    wmove(wmenu, 3, 2);
    waddstr(wmenu, "SCORE");
    wmove(wmenu, 4, 2);
    waddstr(wmenu, "CHANGE NAME");
    wmove(wmenu, 5, 2);
    waddstr(wmenu, "EXIT");
    /*-- initialisation wvisual --*/
    wvisual = newwin(LINES, (COLS/4)*3, 0, COLS/4);
    wrefresh(wvisual);

    update_scr();
}

Ncurses::~Ncurses()
{
    delwin(wmenu);
    endwin();
}

void Ncurses::update_scr()
{
    int i = 0;
    werase(wvisual);
    box(wvisual, 0, 0);
    if (menu == GAMES) {
        mvwaddstr(wmenu, 5, 2, "EXIT");
        wattron(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 1, 2, "GAMES");
        wattroff(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        mvwaddstr(wvisual, 2, 3, "The available games are:");
        for (string game : gamelist) {
            mvwprintw(wvisual, i+3, 4, "| %s", game.c_str());
            i++;
        }
    }
    if (menu == GRAPHLIB) {
        mvwaddstr(wmenu, 1, 2, "GAMES");
        wattron(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        wattroff(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 3, 2, "SCORE");
        mvwaddstr(wvisual, 2, 3, "The available graphical libraries are:");
        for (string lib : liblist) {
            mvwprintw(wvisual, i+3, 4, "| %s", lib.c_str());
            i++;
        }
    }
    if (menu == SCORE) {
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        wattron(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 3, 2, "SCORE");
        wattroff(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        for (string game : gamelist) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(1));
            mvwprintw(wvisual, 2, 4+(18*i), "%s", game.c_str());
            wattroff(wvisual, A_BOLD | COLOR_PAIR(1));
            for (int u = 0; u < 5; u++)
                mvwprintw(wvisual, 3+u, 4+(18*i), "| %i", u*5);
            i++;
        }
    }
    if (menu == CHANGE_NAME) {
        mvwaddstr(wmenu, 3, 2, "SCORE");
        wattron(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        wattroff(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 5, 2, "EXIT");
        mvwaddstr(wvisual, 2, 2, "Enter your name: ");
        wattron(wvisual, COLOR_PAIR(3));
        wprintw(wvisual, "%s", name);
        wattroff(wvisual, COLOR_PAIR(3));
        wattron(wvisual, (A_BLINK| COLOR_PAIR(1)));
        mvwaddstr(wvisual, 5, 2, "Press ENTER to confirm");
        wattroff(wvisual, (A_BLINK| COLOR_PAIR(1)));
    }
    if (menu == EXIT) {
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        wattron(wmenu, COLOR_PAIR(2));
        mvwaddstr(wmenu, 5, 2, "EXIT");
        wattroff(wmenu, COLOR_PAIR(2));
        mvwaddstr(wmenu, 1, 2, "GAMES");
    }
    wrefresh(wmenu);
    wrefresh(wvisual);
}

int Ncurses::displayMenu()
{
    int ch = getch();

    if (ch == KEY_RESIZE) {
        wresize(stdscr, LINES, COLS);
        wresize(wmenu, LINES, COLS/4);
        wresize(wvisual, LINES, (COLS/4)*3);
        clear();
        wclear(wmenu);
        wclear(wvisual);
        refresh();
        wmenu = newwin(LINES, COLS/4, 0, 0);
        box(wmenu, 0, 0);
        wmove(wmenu, 1, 2);
        waddstr(wmenu, "GAMES");
        wmove(wmenu, 2, 2);
        waddstr(wmenu, "GRAPHICAL LIBRARY");
        wmove(wmenu, 3, 2);
        waddstr(wmenu, "SCORE");
        wmove(wmenu, 4, 2);
        waddstr(wmenu, "CHANGE NAME");
        wmove(wmenu, 5, 2);
        waddstr(wmenu, "EXIT");
        mvwin(wvisual, 0, COLS/4);
        box(wvisual, 0, 0);
        update_scr();
    }
    if (ch == KEY_DOWN) {
        menu++;
        update_scr();
    }
    if (ch == KEY_UP) {
        menu--;
        update_scr();
    }
    if (menu == CHANGE_NAME && ch == '\n') {
        wmove(wvisual, 2, 19);
        nodelay(wvisual, FALSE);
        curs_set(1);
        echo();
        waddstr(wvisual, "                              ");
        wmove(wvisual, 2, 19);
        wattron(wvisual, COLOR_PAIR(3));
        wgetnstr(wvisual, name, 30);
        wattroff(wvisual, COLOR_PAIR(3));
        noecho();
        curs_set(0);
        nodelay(wvisual, TRUE);
    }
    if (menu == EXIT && ch == '\n') {
        return 1;
    }
    if (ch == 'q')
        return 1;
    return 0;
}

void Ncurses::displayMap(map_info_t map)
{
    clear();
    refresh();
}
