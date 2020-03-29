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
    RED,
    GREEN,
    BLUE
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

class IGraphLib {
    public:
        virtual ~IGraphLib() = default;
        virtual void setGameList(vector<string>) = 0;
        virtual void setLibList(vector<string>) = 0;
        virtual void init_menu() = 0;
        virtual void init_game() = 0;
        virtual int displayMenu() = 0;
        virtual void displayMap(map_info_t map) = 0;
        virtual int getKey() = 0;
    protected:
    private:
};

#endif /* !IGRAPHLIB_HPP_ */
