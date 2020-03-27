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

using namespace std;

/* MENU */
enum menu_e
{
    GAMES,
    GRAPHLIB,
    SCORE,
    CHANGE_NAME,
    EXIT
};

inline menu_e operator++(menu_e& orig, int)
{
    switch (orig)
    {
    case GAMES:
        return orig = GRAPHLIB;
    case GRAPHLIB:
        return orig = SCORE;
    case SCORE:
        return orig = CHANGE_NAME;
    case CHANGE_NAME:
        return orig = EXIT;
    case EXIT:
        return orig = GAMES;
    default:
        return orig = GAMES;
    }
}
inline menu_e operator--(menu_e& orig, int)
{
    switch (orig)
    {
    case GAMES:
        return orig = EXIT;
    case EXIT:
        return orig = CHANGE_NAME;
    case CHANGE_NAME:
        return orig = SCORE;
    case SCORE:
        return orig = GRAPHLIB;
    case GRAPHLIB:
        return orig = GAMES;
    default:
        return orig = GAMES;
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
        virtual int displayMenu() = 0;
        virtual void displayMap(map_info_t map) = 0;

    protected:
    private:
};

#endif /* !IGRAPHLIB_HPP_ */
