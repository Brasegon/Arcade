/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_

#include "../IGameLib.hpp"
#include <chrono>

enum direction_e {
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
};

enum game_status_e {
    PLAYING,
    LOOSE,
    WIN
};

typedef struct enemy_s {
    position_t pos;
    direction_e direction;
    int life;
    char symbol;
} enemy_t;

typedef struct battery_s {
    position_t pos;
    int id;
} battery_t;

typedef struct shot_s {
    position_t pos;
    int distance;
    direction_e direction;
} shot_t;

typedef struct player_s {
    position_t pos;
    direction_e direction;
    shot_t shot;
} player_t;

class SolarFox: public game_lib
{
    public:
        SolarFox();
        ~SolarFox();
        map_info_t game(playerEvent action);

    private:
    void reset_game();
    void enemies_movement();
    void movement_register(playerEvent action);
    void player_movement();
    void check_enemies_hitbox();
    void playershot_register(playerEvent action);
    void pshot_movement();
    void enemies_check();
    bool game_pause;
    game_status_e game_status;
    map_info_t start_map;
    map_info_t map;
    vector<enemy_t> enemies;
    vector<battery_t> batteries;
    player_t player;
    chrono::high_resolution_clock::time_point clock_start1;
    chrono::high_resolution_clock::time_point clock_start2;
    chrono::high_resolution_clock::time_point clock_start3;
    direction_e direction;
    direction_e direction_register;
};

bool operator!=(position_t pos1, position_t pos2);
bool operator==(position_t pos1, position_t pos2);

#endif /* !SOLARFOX_HPP_ */
