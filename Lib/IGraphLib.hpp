/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** IGraphLib
*/

#ifndef IGRAPHLIB_HPP_
#define IGRAPHLIB_HPP_

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/* MENU */
enum menu_e
{
    MENU_GAMES,
    MENU_GRAPHLIB,
    MENU_SCORE,
    MENU_CHANGE_NAME,
    MENU_EXIT
};

inline menu_e operator++(menu_e& orig, int)
{
    switch (orig)
    {
    case MENU_GAMES:
        return orig = MENU_GRAPHLIB;
    case MENU_GRAPHLIB:
        return orig = MENU_SCORE;
    case MENU_SCORE:
        return orig = MENU_CHANGE_NAME;
    case MENU_CHANGE_NAME:
        return orig = MENU_EXIT;
    case MENU_EXIT:
        return orig = MENU_GAMES;
    default:
        return orig = MENU_GAMES;
    }
}
inline menu_e operator--(menu_e& orig, int)
{
    switch (orig)
    {
    case MENU_GAMES:
        return orig = MENU_EXIT;
    case MENU_EXIT:
        return orig = MENU_CHANGE_NAME;
    case MENU_CHANGE_NAME:
        return orig = MENU_SCORE;
    case MENU_SCORE:
        return orig = MENU_GRAPHLIB;
    case MENU_GRAPHLIB:
        return orig = MENU_GAMES;
    default:
        return orig = MENU_GAMES;
    }
}
/* !MENU */

/* MAP */
typedef enum color_e
{
    RED = 1,
    GREEN,
    BLUE,
    /*...*/
} color_t;

typedef struct position_s
{
    int x;
    int y;
} position_t;

typedef struct pixel_s
{
    color_t color;
    position_t pos;
} pixel_t;

typedef struct map_info_s
{
    vector<pixel_t> pixel;
    vector<string> map;
} map_info_t;
/* !MAP */

enum playerEvent {
    PE_EXIT = -1,
    PE_NOACTION,
    PE_UP,
    PE_DOWN,
    PE_LEFT,
    PE_RIGHT,
    PE_ACTION1,
    PE_ACTION2,
    PE_ACTION3,
    PE_NEXT_GAME,
    PE_PREV_GAME,
    PE_NEXT_LIB,
    PE_PREV_LIB,
    PE_RESTART
};

class IGraphLib {
    public:
        virtual ~IGraphLib() = default;
        virtual void setGameList(vector<string>) = 0;
        virtual void setLibList(vector<string>) = 0;
        virtual void init_menu() = 0;
        virtual void init_game() = 0;
        virtual int displayMenu() = 0;
        virtual void displayMap(map_info_t map) = 0;
        virtual playerEvent getKey() = 0;
    protected:
    private:
};

#endif /* !IGRAPHLIB_HPP_ */
