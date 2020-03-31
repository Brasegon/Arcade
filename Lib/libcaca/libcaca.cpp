/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** libcaca
*/

#include "libcaca.hpp"

CACA::CACA() 
{
    width = 1280/6;
    height = 720/11;

    canvas = caca_create_canvas(width, height);
    display = caca_create_display(canvas);
    if (display == NULL)
        exit(84);
    caca_set_display_title(display, "Arcade");
}

void CACA::setGameList(vector<string> vect)
{

}


void CACA::setLibList(vector<string> vect)
{
    
}

void CACA::init_menu() 
{

}

void CACA::init_game()
{

}

int CACA::displayMenu()
{
    int choose;

    choose = 1; //Snake

    caca_clear_canvas(canvas);
    caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    caca_put_str(canvas, 20, 5, "WELCOME TO CACARCADE !");
    caca_put_str(canvas, 20, 19, "---------");
    caca_put_str(canvas, 20, 20, "| SNAKE |");
    caca_put_str(canvas, 20, 21, "---------");
    caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
    caca_put_str(canvas, 20, 30, "PACMAN");
    caca_refresh_display(display);

    while (42){
        caca_get_event(display, CACA_EVENT_KEY_PRESS, &event, 0);
        if (choose == 1)
        {
            caca_clear_canvas(canvas);
            caca_put_str(canvas, 20, 5, "WELCOME TO CACARCADE !");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 20, 19, "---------");
            caca_put_str(canvas, 20, 20, "| SNAKE |");
            caca_put_str(canvas, 20, 21, "---------");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 20, 30, "PACMAN");
        }
        else if (choose == 0)
        {
            caca_clear_canvas(canvas);
            caca_put_str(canvas, 20, 5, "WELCOME TO CACARCADE !");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 20, 20, "SNAKE");
            caca_set_color_ansi(canvas, CACA_WHITE, CACA_BLACK);
            caca_put_str(canvas, 20, 29, "----------");
            caca_put_str(canvas, 20, 30, "| PACMAN |");
            caca_put_str(canvas, 20, 31, "----------");
        }
        if (caca_get_event_key_ch(&event) == CACA_KEY_UP) {
            choose = 1;
            caca_refresh_display(display);
        }
        if (caca_get_event_key_ch(&event) == CACA_KEY_DOWN) {
            choose = 0;
            caca_refresh_display(display);
        }
        if (caca_get_event_key_ch(&event) == CACA_KEY_ESCAPE)
        {
            caca_free_canvas(canvas);
            exit(0);
        }
        if (caca_get_event_key_ch(&event) == 13)
            break;
        if (caca_get_event_type(&event) == CACA_EVENT_KEY_PRESS)
            caca_refresh_display(display);
    }
    return (choose);
}

void CACA::displayMap(map_info_t map)
{
    caca_clear_canvas(canvas);
    for (int x = 0; x < map.map.size(); x += 1) {
        for (int y = 0; y < map.map[x].size(); y += 1) {
            caca_put_str(canvas, x, y, &map.map[y][x]);
        }
    }
    caca_refresh_display(display);
}

playerEvent CACA::getKey() 
{
    caca_get_event(display, CACA_EVENT_KEY_PRESS, &event, 0);
    switch (caca_get_event_key_ch(&event))
    {
    case 'q':
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

CACA::~CACA()
{
    caca_free_canvas(canvas);
    caca_free_display(display);
}