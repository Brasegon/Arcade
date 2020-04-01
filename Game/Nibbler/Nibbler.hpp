/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "../IGameLib.hpp"
#include <iostream>
#include <string>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <ratio>

typedef struct apple_s {
    position_t pos;
    bool eaten;
} apple_t;

class Nibbler: public game_lib
{
    public:
        Nibbler();
        ~Nibbler();
        map_info_t game(playerEvent action);
    protected:
    private:
        int move_body();
        void reset_game();
        void generate_apple();
        map_info_t start_map;
        map_info_t map;
        vector<position_t> start_body;
        vector<position_t> body;
        apple_t apple;
        playerEvent direction;
        playerEvent direction_register;
        chrono::high_resolution_clock::time_point clock_start;
        bool game_pause;
        int i_pixel_head;
        int game_speed;
};

bool operator==(apple_t apple, vector<position_t> vect);
bool operator==(position_t, vector<position_t>);
bool operator==(position_t pos1, position_t pos2);
bool operator!=(position_t pos1, position_t pos2);

#endif /* !NIBBLER_HPP_ */
