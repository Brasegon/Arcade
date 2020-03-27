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
    RESTART,
    SCORE,
    CHANGE_NAME,
    CHANGE_GAME,
    CHANGE_LIB,
    EXIT
};

inline menu_e operator++(menu_e& orig, int)
{
    switch (orig)
    {
    case RESTART:
        return orig = SCORE;
    case SCORE:
        return orig = CHANGE_NAME;
    case CHANGE_NAME:
        return orig = CHANGE_GAME;
    case CHANGE_GAME:
        return orig = CHANGE_LIB;
    case CHANGE_LIB:
        return orig = EXIT;
    case EXIT:
        return orig = RESTART;
    default:
        return orig = RESTART;
    }
}
inline menu_e operator--(menu_e& orig, int)
{
    switch (orig)
    {
    case RESTART:
        return orig = EXIT;
    case EXIT:
        return orig = CHANGE_LIB;
    case CHANGE_LIB:
        return orig = CHANGE_GAME;
    case CHANGE_GAME:
        return orig = CHANGE_NAME;
    case CHANGE_NAME:
        return orig = SCORE;
    case SCORE:
        return orig = RESTART;
    default:
        return orig = RESTART;
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
