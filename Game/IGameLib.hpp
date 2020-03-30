/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** IGameLib
*/

#ifndef IGAMELIB_HPP_
#define IGAMELIB_HPP_

#include "../Lib/IGraphLib.hpp"


enum playerEvent {
    PE_NOACTION,
    PE_UP,
    PE_DOWN,
    PE_LEFT,
    PE_RIGHT
};

class game_lib {
    public:
        virtual ~game_lib() = default;
        virtual map_info_t game(playerEvent action) = 0;
        // void *handle;
};

#endif /* !IGAMELIB_HPP_ */
