/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** libcaca
*/
#include <sstream>
#include <string>
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
    for (string game : list) {
        game.erase(game.end()-3, game.end());
        sscanf(game.c_str(), "./Game/lib_arcade_%s", gameName);
        gamelist.push_back(gameName);
    }
}


void CACA::setLibList(vector<string> list)
{
    char libName[50];
    for (string lib : list) {
        lib.erase(lib.end()-3, lib.end());
        sscanf(lib.c_str(), "./Lib/lib_arcade_%s", libName);
        liblist.push_back(libName);
    }
}

void CACA::init_menu() 
{
    choose = 0;

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

    for (string game : gamelist) {
        caca_put_str(canvas, (width/3) + 6, 4, "| ");
        caca_put_str(canvas, (width/3) + 7, 4, game.c_str());
    }
}

void CACA::init_game()
{
    caca_free_canvas(canvas);
    caca_free_display(display);
    game_canvas = caca_create_canvas(23, 22);
    display = caca_create_display(game_canvas);
}

int CACA::displayMenu()
{
    caca_refresh_display(display);

        // std::cout << choose << std::endl;
        caca_event_t event;
        int key = 0;
        caca_get_event(display, CACA_EVENT_KEY_PRESS, &event, -1);
        key = caca_get_event_key_ch(&event);
        if (key == CACA_KEY_UP) {
            if (choose > 0)
                choose--;
        }
        if (key == CACA_KEY_DOWN) {
            if (choose < 4)
                choose++;
        }
        if (key == CACA_KEY_ESCAPE || key == 'q' || (choose == 4 && key == CACA_KEY_RETURN))
        {
            return (-1);
        }
        // if (key == 13)
        //     break;
        // if (caca_get_event_type(&event) == CACA_EVENT_KEY_PRESS)
        //     caca_refresh_display(display);

        if (choose == 0) {
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
            caca_put_str(canvas, 5, 7, tostr(choose).c_str());

            caca_put_str(canvas, (width/3) + 5, 3, "The available games are:");
            for (string game : gamelist) {
                caca_put_str(canvas, (width/3) + 6, 4, "| ");
                caca_put_str(canvas, (width/3) + 7, 4, game.c_str());
            }
        }
        else if (choose == 1) {
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
            caca_put_str(canvas, 5, 7, tostr(choose).c_str());

            caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
            for (string lib : liblist) {
                caca_put_str(canvas, (width/3) + 6, 4, "| ");
                caca_put_str(canvas, (width/3) + 7, 4, lib.c_str());
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
            caca_put_str(canvas, 5, 3, "GRAPHICAL LIBRARY");
            caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
            caca_put_str(canvas, 5, 4, "SCORE");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 5, 5, "CHANGE NAME");
            caca_put_str(canvas, 5, 6, "EXIT");
            caca_put_str(canvas, 5, 7, tostr(choose).c_str());

            // caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
            // i = 0;
            // for (string lib : liblist) {
            //     caca_put_str(canvas, (width/3) + 6, 4 + i, "| ");
            //     caca_put_str(canvas, (width/3) + 7, 4 + i, lib.c_str());
            // }
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
            caca_put_str(canvas, 5, 4, "SCORE");
            caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
            caca_put_str(canvas, 5, 5, "CHANGE NAME");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 5, 6, "EXIT");
            caca_put_str(canvas, 5, 7, tostr(choose).c_str());

            // caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
            // i = 0;
            // for (string lib : liblist) {
            //     caca_put_str(canvas, (width/3) + 6, 4 + i, "| ");
            //     caca_put_str(canvas, (width/3) + 7, 4 + i, lib.c_str());
            // }
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
            caca_put_str(canvas, 5, 5, "CHANGE NAME");
            caca_set_color_ansi(canvas, CACA_CYAN, CACA_BLACK);
            caca_put_str(canvas, 5, 6, "EXIT");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 5, 7, tostr(choose).c_str());

            // caca_put_str(canvas, (width/3) + 5, 3, "The available graphical libraries are:");
            // i = 0;
            // for (string lib : liblist) {
            //     caca_put_str(canvas, (width/3) + 6, 4 + i, "| ");
            //     caca_put_str(canvas, (width/3) + 7, 4 + i, lib.c_str());
            // }
        }

    // }
    return (0);
}

void CACA::displayMap(map_info_t map)
{
    caca_clear_canvas(game_canvas);
    for (int x = 0; x < map.map.size(); x += 1) {
        for (int y = 0; y < map.map[x].size(); y += 1) {
            switch (map.map[y][x]) {
            case 'X':
                caca_set_color_ansi(game_canvas, CACA_LIGHTCYAN, CACA_BLACK);
                break;
            case 'P':
                caca_set_color_ansi(game_canvas, CACA_RED, CACA_BLACK);
                break;
            case 'O':
                caca_set_color_ansi(game_canvas, CACA_GREEN, CACA_BLACK);
                break;
            case '<':
                caca_set_color_ansi(game_canvas, CACA_GREEN, CACA_BLACK);
                break;
            case 'A':
                caca_set_color_ansi(game_canvas, CACA_GREEN, CACA_BLACK);
                break;
            case '>':
                caca_set_color_ansi(game_canvas, CACA_GREEN, CACA_BLACK);
                break;
            case 'V':
                caca_set_color_ansi(game_canvas, CACA_GREEN, CACA_BLACK);
                break;
            default:
                caca_set_color_ansi(game_canvas, CACA_WHITE, CACA_BLACK);
                break;
            }
            caca_put_char(game_canvas, x, y, map.map[y][x]);
        }
    }
    caca_refresh_display(display);
}

playerEvent CACA::getKey() 
{
    caca_event_t event;
    caca_get_event(display, CACA_EVENT_KEY_PRESS, &event, 0);
    switch (caca_get_event_key_ch(&event))
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