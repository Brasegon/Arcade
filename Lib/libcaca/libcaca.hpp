/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** libcaca
*/

#ifndef LIBCACA_HPP_
#define LIBCACA_HPP_

#include "../IGraphLib.hpp"
#include "caca/caca.h"

class CACA : public IGraphLib
{
    public:
        CACA();
        ~CACA();
        void setGameList(vector<string>);
        void setLibList(vector<string>);
        void init_menu();
        void init_game();
        int displayMenu();
        void displayMap(map_info_t map);
        playerEvent getKey();

        caca_canvas_t *canvas;
        caca_canvas_t *game_canvas;
        caca_display_t *display;
        caca_font_t *font;
        int width;
        int height;

        vector<string> gamelist;
        vector<string> liblist;
        int choose;

    protected:
    private:
};

#endif /* !LIBCACA_HPP_ */
