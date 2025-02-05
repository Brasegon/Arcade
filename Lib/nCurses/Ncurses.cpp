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
    playerName = "player";
    /*-- initialisation stdscr --*/
    initscr();
    curs_set(0);
    noecho();
    raw();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(RED, COLOR_RED, COLOR_RED);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(CYAN, COLOR_CYAN, COLOR_CYAN);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(WHITE+1, COLOR_RED, COLOR_BLACK);
    init_pair(WHITE+2, COLOR_GREEN, COLOR_BLACK);
    init_pair(WHITE+3, COLOR_BLUE, COLOR_BLACK);
    init_pair(WHITE+4, COLOR_BLUE, COLOR_GREEN);
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
    char gameName[50];

    gamelist.clear();
    for (string game : list) {
        game.erase(game.end()-3, game.end());
        sscanf(game.c_str(), "./Game/lib_arcade_%s", gameName);
        gamelist.push_back(gameName);
    }
}

void Ncurses::setLibList(vector<string> list)
{
    char libName[50];

    liblist.clear();
    for (string lib : list) {
        lib.erase(lib.end()-3, lib.end());
        sscanf(lib.c_str(), "./Lib/lib_arcade_%s", libName);
        liblist.push_back(libName);
    }
}

// update les fenêtres du menu
void Ncurses::update_scr()
{
    int i = 0;
    werase(wvisual);
    box(wvisual, 0, 0);
    if (menu == MENU_GAMES) {
        mvwaddstr(wmenu, 5, 2, "EXIT");
        wattron(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 1, 2, "GAMES");
        wattroff(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        if (gamelist.empty()) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(WHITE+1));
            mvwaddstr(wvisual, 2, 4, "No games found");
            wattroff(wvisual, A_BOLD | COLOR_PAIR(WHITE+1));
        }
        else
            mvwaddstr(wvisual, 2, 3, "The available games are:");
        for (string game : gamelist) {
            mvwaddstr(wvisual, i+3, 4, "| ");
            wattron(wvisual, COLOR_PAIR(WHITE+3));
            waddstr(wvisual, game.c_str());
            wattroff(wvisual, COLOR_PAIR(WHITE+3));
            i++;
        }
    }
    if (menu == MENU_GRAPHLIB) {
        mvwaddstr(wmenu, 1, 2, "GAMES");
        wattron(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        wattroff(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 3, 2, "SCORE");
        mvwaddstr(wvisual, 2, 3, "The available graphical libraries are:");
        for (string lib : liblist) {
            mvwaddstr(wvisual, i+3, 4, "| ");
            wattron(wvisual, COLOR_PAIR(WHITE+3));
            waddstr(wvisual, lib.c_str());
            wattroff(wvisual, COLOR_PAIR(WHITE+3));
            i++;
        }
    }
    if (menu == MENU_SCORE) {
        mvwaddstr(wmenu, 2, 2, "GRAPHICAL LIBRARY");
        wattron(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 3, 2, "SCORE");
        wattroff(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        if (gamelist.empty()) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(WHITE+1));
            mvwaddstr(wvisual, 2, 4, "No games found");
            wattroff(wvisual, A_BOLD | COLOR_PAIR(WHITE+3));
        }
        for (string game : gamelist) {
            wattron(wvisual, A_BOLD | COLOR_PAIR(WHITE+3));
            mvwprintw(wvisual, 2, 4+(18*i), "%s", game.c_str());
            wattroff(wvisual, A_BOLD | COLOR_PAIR(WHITE+3));
            for (int u = 0; u < 5; u++)
                mvwprintw(wvisual, 3+u, 4+(18*i), "| %i", u*5);
            i++;
        }
    }
    if (menu == MENU_CHANGE_NAME) {
        mvwaddstr(wmenu, 3, 2, "SCORE");
        wattron(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        wattroff(wmenu, COLOR_PAIR(WHITE+3));
        mvwaddstr(wmenu, 5, 2, "EXIT");
        mvwaddstr(wvisual, 2, 2, "Enter your name: ");
        wattron(wvisual, COLOR_PAIR(WHITE+2));
        wprintw(wvisual, "%s", playerName.c_str());
        wattroff(wvisual, COLOR_PAIR(WHITE+2));
        wattron(wvisual, (A_BLINK| COLOR_PAIR(WHITE+3)));
        mvwaddstr(wvisual, 5, 2, "Press ENTER to confirm");
        wattroff(wvisual, (A_BLINK| COLOR_PAIR(WHITE+3)));
    }
    if (menu == MENU_EXIT) {
        mvwaddstr(wmenu, 4, 2, "CHANGE NAME");
        wattron(wmenu, COLOR_PAIR(WHITE+1));
        mvwaddstr(wmenu, 5, 2, "EXIT");
        wattroff(wmenu, COLOR_PAIR(WHITE+1));
        mvwaddstr(wmenu, 1, 2, "GAMES");
    }
    wrefresh(wmenu);
    wrefresh(wvisual);
}

// affiche le menu
playerEvent Ncurses::displayMenu()
{
    char name[31];
    int ch = getch();

    if (ch == KEY_RESIZE) {
        wresize(stdscr, LINES, COLS);
        wresize(wmenu, LINES, COLS/4);
        wresize(wvisual, LINES, (COLS/4)*3);
        clear();
        wclear(wmenu);
        wclear(wvisual);
        refresh();
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
        return PE_RESTART;
    }
    if (menu == MENU_CHANGE_NAME && ch == '\n') {
        wmove(wvisual, 2, 19);
        nodelay(wvisual, FALSE);
        curs_set(1);
        echo();
        waddstr(wvisual, "                              ");
        wmove(wvisual, 2, 19);
        wattron(wvisual, COLOR_PAIR(WHITE+2));
        wgetnstr(wvisual, name, 30);
        wattroff(wvisual, COLOR_PAIR(WHITE+2));
        noecho();
        curs_set(0);
        nodelay(wvisual, TRUE);
        playerName = name;
    }
    if (menu == MENU_EXIT && ch == '\n') {
        return PE_EXIT;
    }
    switch (ch)
    {
    case 'q':
        return PE_EXIT;
    case 'g':
        return PE_NEXT_GAME;
    case 'f':
        return PE_PREV_GAME;
    case 'l':
        return PE_NEXT_LIB;
    case 'k':
        return PE_PREV_LIB;
    case 'r':
        return PE_RESTART;
    default:
        return PE_NOACTION;
    }
}

// affiche la map envoyée par le jeu
void Ncurses::displayMap(map_info_t map)
{
                    /*  + - / { } [ ] ( ) : ;  */
                    /*  ╋ ━ ┃ ┗ ┛ ┏ ┓ ┣ ┫ ┻ ┳  */
    int i = 0;
    char c = 0;
    erase();
    for (int y = 1; y < map.map.size()-1; y++) {
        for (int x = 1; x < map.map.size()-1; x++) {
            c = map.map[y][x];
            mvaddch(y+1, x+1, c);
            if (c == '+') {
                mvaddch(y+1, x+1, ACS_PLUS);
            }
            if (c == '-') {
                mvaddch(y+1, x+1, ACS_HLINE);
            }
            if (c == '/') {
                mvaddch(y+1, x+1, ACS_VLINE);
            }
            if (c == '{') {
                mvaddch(y+1, x+1, ACS_LLCORNER);
            }
            if (c == '}') {
                mvaddch(y+1, x+1, ACS_LRCORNER);
            }
            if (c == '[') {
                mvaddch(y+1, x+1, ACS_ULCORNER);
            }
            if (c == ']') {
                mvaddch(y+1, x+1, ACS_URCORNER);
            }
            if (c == '(') {
                mvaddch(y+1, x+1, ACS_LTEE);
            }
            if (c == ')') {
                mvaddch(y+1, x+1, ACS_RTEE);
            }
            if (c == ':') {
                mvaddch(y+1, x+1, ACS_BTEE);
            }
            if (c == ';') {
                mvaddch(y+1, x+1, ACS_TTEE);
            }
        }
    }
    mvaddstr(map.map.size()+2, 1, "player name : ");
    attron(COLOR_PAIR(WHITE+2));
    addstr(playerName.c_str());
    attroff(COLOR_PAIR(WHITE+2));
    addstr("  |  score : ");
    attron(COLOR_PAIR(WHITE+2));
    printw("%i", map.score);
    attroff(COLOR_PAIR(WHITE+2));

    for (pixel_t pixel : map.pixel) {
        c = map.map[pixel.pos.y][pixel.pos.x];
        if ((c == '^' ||c == 'v'||c == '<' ||c == '>') && pixel.color == GREEN) {
            mvchgat(pixel.pos.y+1, pixel.pos.x+1, 1, A_NORMAL, WHITE+4, NULL);
            continue;
        }
        mvchgat(pixel.pos.y+1, pixel.pos.x+1, 1, A_NORMAL, pixel.color, NULL);
    }
    refresh();
}

void Ncurses::save_score()
{
}

playerEvent Ncurses::getKey()
{
    switch (getch())
    {
    case 'q':
        return PE_EXIT;
    case KEY_UP:
        return PE_UP;
    case KEY_DOWN:
        return PE_DOWN;
    case KEY_LEFT:
        return PE_LEFT;
    case KEY_RIGHT:
        return PE_RIGHT;
    case 'a':
        return PE_ACTION1;
    case 'z':
        return PE_ACTION2;
    case 'e':
        return PE_ACTION3;
    case 'g':
        clear();
        refresh();
        return PE_NEXT_GAME;
    case 'f':
        clear();
        refresh();
        return PE_PREV_GAME;
    case 'l':
        clear();
        refresh();
        return PE_NEXT_LIB;
    case 'k':
        clear();
        refresh();
        return PE_PREV_LIB;
    case 'r':
        return PE_RESTART;
    default:
        return PE_NOACTION;
    }
}
