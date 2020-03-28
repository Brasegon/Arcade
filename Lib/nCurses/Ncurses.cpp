/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

//contructeur
Ncurses::Ncurses()
{
    menu = MENU_GAMES;
    name[0] = 'p';
    name[1] = 'l';
    name[2] = 'a';
    name[3] = 'y';
    name[4] = 'e';
    name[5] = 'r';
    name[6] = '\0';
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
}

//destructeur
Ncurses::~Ncurses()
{
    delwin(wmenu);
    delwin(wvisual);
    endwin();
}

// Initialisation de wmenu
void Ncurses::init_menu()
{
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

void Ncurses::init_game()
{
    clear();
}

void Ncurses::setGameList(vector<string> list)
{
    gamelist = list;
}

void Ncurses::setLibList(vector<string> list)
{
    liblist = list;
}

// update les fenêtres du menu
void Ncurses::update_scr()
{
    int i = 0;
    werase(wvisual);
    box(wvisual, 0, 0);
    if (menu == MENU_GAMES) {
        mvwaddstr(wmenu, 5, 2, "EXIT");
        wattron(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 1, 2, "GAMES");
        wattroff(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        if (gamelist.empty()) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(2));
            mvwaddstr(wvisual, 2, 4, "No games found");
            wattroff(wvisual, A_BOLD | COLOR_PAIR(1));
        }
        else
            mvwaddstr(wvisual, 2, 3, "The available games are:");
        for (string game : gamelist) {
            mvwprintw(wvisual, i+3, 4, "| %s", game.c_str());
            i++;
        }
    }
    if (menu == MENU_GRAPHLIB) {
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
    if (menu == MENU_SCORE) {
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        wattron(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 3, 2, "SCORE");
        wattroff(wmenu, COLOR_PAIR(1));
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        if (gamelist.empty()) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(2));
            mvwaddstr(wvisual, 2, 4, "No games found");
            wattroff(wvisual, A_BOLD | COLOR_PAIR(1));
        }
        for (string game : gamelist) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(1));
            mvwprintw(wvisual, 2, 4+(18*i), "%s", game.c_str());
            wattroff(wvisual, A_BOLD | COLOR_PAIR(1));
            for (int u = 0; u < 5; u++)
                mvwprintw(wvisual, 3+u, 4+(18*i), "| %i", u*5);
            i++;
        }
    }
    if (menu == MENU_CHANGE_NAME) {
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
    if (menu == MENU_EXIT) {
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        wattron(wmenu, COLOR_PAIR(2));
        mvwaddstr(wmenu, 5, 2, "EXIT");
        wattroff(wmenu, COLOR_PAIR(2));
        mvwaddstr(wmenu, 1, 2, "GAMES");
    }
    wrefresh(wmenu);
    wrefresh(wvisual);
}

// affiche le menu
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
    if (menu == MENU_GAMES && ch == '\n') {
        return 1;
    }
    if (menu == MENU_CHANGE_NAME && ch == '\n') {
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
    if (menu == MENU_EXIT && ch == '\n') {
        return -1;
    }
    if (ch == 'q')
        return -1;
    return 0;
}

// affiche la map envoyée par le jeu
void Ncurses::displayMap(map_info_t map)
{
    int i = 0;
    erase();
    for (string line : map.map) {
        mvaddstr(1+i, 1, line.c_str());
        i++;
    }
    refresh();
}

int Ncurses::getKey()
{
    return getch();
}
