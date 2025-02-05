/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** libcaca
*/


#include "libcaca.hpp"

std::string tostr (int x)
{
    std::stringstream str;
    str << x;
    return str.str();
}

CACA::CACA() 
{
    width = /* 23 */ 1280/6;
    height = /* 22 */ 720/11;
    player_name = "Player";

    canvas = caca_create_canvas(width, height);
    display = caca_create_display(canvas);
    // font = caca_load_font("ARCADE_N.TTF", 50);
    // caca_render_canvas(canvas, font, NULL, width, height, 0);
    if (display == NULL)
        exit(84);
    caca_set_display_title(display, "Arcade");
}

void CACA::setGameList(vector<string> list)
{
    char gameName[50];
    gamelist.clear();
    for (string game : list) {
        game.erase(game.end()-3, game.end());
        sscanf(game.c_str(), "./Game/lib_arcade_%s", gameName);
        gamelist.push_back(gameName);
    }
}


void CACA::setLibList(vector<string> list)
{
    char libName[50];
    liblist.clear();
    for (string lib : list) {
        lib.erase(lib.end()-3, lib.end());
        sscanf(lib.c_str(), "./Lib/lib_arcade_%s", libName);
        liblist.push_back(libName);
        // std::cout << libName << std::endl;
    }
}

void CACA::init_menu() 
{
    choose = 1;
    int i = 0;

    caca_clear_canvas(canvas);
    caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    for (int y = 0; y != height; y = y + 1) {
        for (int x = 0; x != width ; x = x + 1) {
            if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                caca_put_str(canvas, x, y, "─");
            if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                caca_put_str(canvas, x, y, "│");
            if (x == 0 && y == 0 || x == (width/3) && y == 0)
                caca_put_str(canvas, x, y, "┌");
            if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                caca_put_str(canvas, x, y, "┐");
            if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                caca_put_str(canvas, x, y, "└");
            if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                caca_put_str(canvas, x, height - 1, "┘");
        }
    }
    caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
    caca_put_str(canvas, 5, 2, "GAME");
    caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
    caca_put_str(canvas, 5, 4, "SCORE");
    caca_put_str(canvas, 5, 5, "CHANGE NAME");
    caca_put_str(canvas, 5, 6, "EXIT");
    
    caca_put_str(canvas, (width/3) + 5, 3, "The available games are:");
    i = 0;
    for (string game : gamelist) {
        caca_put_str(canvas, (width/3) + 6, 4 + i, "|   ");
        caca_put_str(canvas, (width/3) + 9, 4 + i, game.c_str());
        i = i + 1;
    }
}

void CACA::init_game()
{
}

playerEvent CACA::displayMenu()
{
    caca_refresh_display(display);
    caca_event_t event;
    int key = 0;
    int i = 0;
    static int selected = 0;
    static int old_choose = 0;

    caca_get_event(display, CACA_EVENT_KEY_PRESS, &event, 0);
    if (event.type == CACA_EVENT_KEY_PRESS)
        key = caca_get_event_key_ch(&event);
    if (key == CACA_KEY_UP) {
        // std::cout << "up" << std::endl;
        if (selected == 0) {
            if (choose > 0)
                choose--;
        }
        else {
            if (selected > 10 && selected <= 11) {
                // std::cout << "selected > 10 && selected <= 11" << std::endl;
                selected = selected - 1;
            }
            if (selected > 20 && selected <= 22) {
                // std::cout << "selected > 20 && selected <= 29" << std::endl;
                selected = selected - 1;
            }
        }
    }
    if (key == CACA_KEY_DOWN) {
        // std::cout << "down" << std::endl;
        if (selected == 0) {
            if (choose > 0 || choose < 4)
                choose++;
        }
        else {
            if (selected < 11 && selected >= 10) {
                // std::cout << "selected < 11 && selected >= 10" << std::endl;
                selected = selected + 1;
            }
            if (selected < 22 && selected >= 20) {
                // std::cout << "selected < 29 && selected >= 20" << std::endl;
                selected = selected + 1;
            }
        }
    }
    // std::cout << selected << std::endl;
    if (key == CACA_KEY_ESCAPE || key == 'q' /*|| (choose == 4 && key == CACA_KEY_RETURN)*/) {
        return (PE_EXIT);
    }
    if (key == CACA_KEY_RETURN) {
        if (selected < 9 && old_choose == 0 && choose != 3) {
            selected = choose * 10;
            old_choose = choose;
            choose = 0;
        }
        else {
            // std::cout << selected << std::endl;
            if (selected == 10)
                return (PE_RESTART);
            if (selected == 11)
                return (PE_RESTART);
        }
        // std::cout << selected << std::endl;
    }
    if (key == CACA_KEY_DELETE) {
        choose = old_choose;
        selected = 0;
        old_choose = 0;
    }

    if (selected == 10) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");
        // caca_put_str(canvas, 5, 7, tostr(choose).c_str());

        caca_put_str(canvas, (width/3) + 5, 3, "The available games are:");
        i = 0;
        for (string game : gamelist) {
            if (i == 0) {
                caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, game.c_str());
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                // std::cout << "i = " << i << " | game_name = " << game.c_str() << std::endl;
            }
            else {
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, game.c_str());
            }
            i = i + 1;
        }
    }
    else if (selected == 11) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");
        // caca_put_str(canvas, 5, 7, tostr(choose).c_str());

        caca_put_str(canvas, (width/3) + 5, 3, "The available games are:");
        i = 0;
        for (string game : gamelist) {
            if (i == 1) {
                caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, game.c_str());
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                // std::cout << "i = " << i << " | game_name = " << game.c_str() << std::endl;
            }
            else {
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, game.c_str());
            }
            i = i + 1;
        }
    }
    else if (selected == 20) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");
        // caca_put_str(canvas, 5, 7, tostr(choose).c_str());

        caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
        i = 0;
        for (string lib : liblist) {
            if (i == 0) {
                caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                // std::cout << "i = " << i << " | game_name = " << game.c_str() << std::endl;
            }
            else {
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
            }
            i = i + 1;
        }
    }
    else if (selected == 21) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");
        // caca_put_str(canvas, 5, 7, tostr(choose).c_str());

        caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
        i = 0;
        for (string lib : liblist) {
            if (i == 1) {
                caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                // std::cout << "i = " << i << " | game_name = " << game.c_str() << std::endl;
            }
            else {
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
            }
            i = i + 1;
        }
    }
    else if (selected == 22) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");
        // caca_put_str(canvas, 5, 7, tostr(choose).c_str());

        caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
        i = 0;
        for (string lib : liblist) {
            if (i == 2) {
                caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                // std::cout << "i = " << i << " | game_name = " << game.c_str() << std::endl;
            }
            else {
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
            }
            i = i + 1;
        }
    }
    else if (selected == 23) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");
        // caca_put_str(canvas, 5, 7, tostr(choose).c_str());

        caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
        i = 0;
        for (string lib : liblist) {
            if (i == 0) {
                caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                // std::cout << "i = " << i << " | game_name = " << game.c_str() << std::endl;
            }
            else {
                caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
                caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
            }
            i = i + 1;
        }
    }
    else if (selected == 40) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 6, "EXIT");

        caca_put_str(canvas, (width/3) + 5, 3, "Enter your name: ");
        caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
        caca_put_str(canvas, (width/3) + 22, 3, player_name.c_str());
        caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        caca_put_str(canvas, (width/3) + 5, 21, "Press ENTER to confirm");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    }

    // -------------------------------------------------------------------------------------------------------------------------------------------------

    if (choose == 1) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");

        caca_put_str(canvas, (width/3) + 5, 3, "The available games are:");
        i = 0;
        for (string game : gamelist) {
            caca_put_str(canvas, (width/3) + 6, 4 + i, "|");
            caca_put_str(canvas, (width/3) + 9, 4 + i, game.c_str());
            i = i + 1;
        }
    }
    else if (choose == 2) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");

        caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
        i = 0;
        for (string lib : liblist) {
            caca_put_str(canvas, (width/3) + 6, 4 + i, "| ");
            caca_put_str(canvas, (width/3) + 9, 4 + i, lib.c_str());
            i = i + 1;
        }
    }
    else if (choose == 3) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_put_str(canvas, 5, 6, "EXIT");

        i = 0;
        for (string game : gamelist) {
            caca_put_str(canvas, (width/3) + 5 + i, 3, game.c_str());
            for (int i_i = 0; i_i != 5; i_i = i_i + 1)
                caca_put_str(canvas, (width/3) + 7 + i , 4 + i_i, tostr(i_i * 5).c_str());
            i = i + 20;
        }
    }
    else if (choose == 4) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        caca_put_str(canvas, 5, 6, "EXIT");

        caca_put_str(canvas, (width/3) + 5, 3, "Enter your name: ");
        caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
        caca_put_str(canvas, (width/3) + 22, 3, player_name.c_str());
        // caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLACK);
        // caca_put_str(canvas, (width/3) + 5, 21, "");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    }
    else if (choose == 5) {
        caca_clear_canvas(canvas);
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
        for (int y = 0; y != height; y = y + 1) {
            for (int x = 0; x != width ; x = x + 1) {
                if ((x != 0 && x != (width/3) - 1 && y == 0) || (x != 0 && x != (width/3) - 1 && y == height - 1))
                    caca_put_str(canvas, x, y, "─");
                if ((x == 0 && y != 0 && y != height - 1) || (x == (width/3) - 1 && y != 0 && y != height - 1) || x == (width/3) && y != 0 || x == width - 1 && y != height - 1)
                    caca_put_str(canvas, x, y, "│");
                if (x == 0 && y == 0 || x == (width/3) && y == 0)
                    caca_put_str(canvas, x, y, "┌");
                if (x == (width/3) - 1 && y == 0 || x == width - 1 && y == 0)
                    caca_put_str(canvas, x, y, "┐");
                if (x == 0 && y == height - 1 || x == (width/3) && y == height - 1)
                    caca_put_str(canvas, x, y, "└");
                if (x == (width/3) - 1 && y == height - 1 || x == width - 1 && y == height - 1)
                    caca_put_str(canvas, x, height - 1, "┘");
            }
        }
        caca_put_str(canvas, 5, 2, "GAME");
        caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
        caca_put_str(canvas, 5, 4, "SCORE");
        caca_put_str(canvas, 5, 5, "CHANGE NAME");
        caca_set_color_ansi(canvas, CACA_RED, CACA_BLACK);
        caca_put_str(canvas, 5, 6, "EXIT");
        caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    }
    switch (key)
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

void CACA::displayMap(map_info_t map)
{
    caca_clear_canvas(canvas);
    for (int y = 0; y < map.map.size(); y += 1) {
        for (int x = 0; x < map.map[y].size(); x += 1) {
            switch (map.map[y][x]) {
            case 'X':
                caca_set_color_ansi(canvas, CACA_LIGHTCYAN, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case 'P':
                caca_set_color_ansi(canvas, CACA_RED, CACA_RED);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case 'B':
                caca_set_color_ansi(canvas, CACA_YELLOW, CACA_YELLOW);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case 'E':
                caca_set_color_ansi(canvas, CACA_MAGENTA, CACA_MAGENTA);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case '6':
                caca_set_color_ansi(canvas, CACA_RED, CACA_RED);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case 'o':
                caca_set_color_ansi(canvas, CACA_BLUE, CACA_BLUE);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case 'O':
                caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case '<':
                caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case '^':
                caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case '>':
                caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            case 'v':
                caca_set_color_ansi(canvas, CACA_GREEN, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
                /*  + - / { } [ ] ( ) : ;  */
                /*  ┼ ─ │ └ ┘ ┌ ┐ ├ ┤ ┴ ┬  */
            case '+':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┼");
                break;
            case '-':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "─");
                break;
            case '/':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "│");
                break;
            case '{':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "└");
                break;
            case '}':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┘");
                break;
            case '[':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┌");
                break;
            case ']':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┐");
                break;
            case '(':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "├");
                break;
            case ')':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┤");
                break;
            case ':':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┴");
                break;
            case ';':
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_str(canvas, x, y, "┬");
                break;
            case 'T':
                caca_set_color_ansi(canvas, CACA_BLACK, CACA_BLACK);
                caca_put_str(canvas, x, y, "T");
                break;
            default:
                caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
                caca_put_char(canvas, x, y, map.map[y][x]);
                break;
            }
        }
    }
    caca_refresh_display(display);
}

playerEvent CACA::getKey() 
{
    caca_event_t event;
    int key = 0;

    caca_get_event(display, CACA_EVENT_KEY_PRESS, &event, 0);
    if (event.type == CACA_EVENT_KEY_PRESS)
        key = caca_get_event_key_ch(&event);
    switch (key)
    {
    case 'q':
        return PE_EXIT;
    case 'Q':
        return PE_EXIT;
    case CACA_KEY_UP:
        return PE_UP;
    case CACA_KEY_DOWN:
        return PE_DOWN;
    case CACA_KEY_LEFT:
        return PE_LEFT;
    case CACA_KEY_RIGHT:
        return PE_RIGHT;
    case 'a':
        return PE_ACTION1;
    case 'A':
        return PE_ACTION1;
    case 'z':
        return PE_ACTION2;
    case 'Z':
        return PE_ACTION2;
    case 'e':
        return PE_ACTION3;
    case 'E':
        return PE_ACTION3;
    case 'g':
        return PE_NEXT_GAME;
    case 'G':
        return PE_NEXT_GAME;
    case 'f':
        return PE_PREV_GAME;
    case 'F':
        return PE_PREV_GAME;
    case 'l':
        return PE_NEXT_LIB;
    case 'L':
        return PE_NEXT_LIB;
    case 'k':
        return PE_PREV_LIB;
    case 'K':
        return PE_PREV_LIB;
    case 'r':
        return PE_RESTART;
    case 'R':
        return PE_RESTART;
    default:
        return PE_NOACTION;
    }
}

CACA::~CACA()
{
    caca_free_canvas(canvas);
    caca_free_display(display);
}