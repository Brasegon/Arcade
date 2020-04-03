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
#include <thread>

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
    direction_e canon_orientation;
    int life;
    char symbol;
} enemy_t;

typedef struct battery_s {
    position_t pos;
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
        void *handle;

    private:
    void reset_game();
    void generate_colors();
    void generate_path();
    void check_batteries();
    bool enemy_trail(int n);
    void enemies_movement();
    void movement_register(playerEvent action);
    void player_movement();
    void check_all_hitboxes();
    void playershot_register(playerEvent action);
    void pshot_movement();
    void enemies_check();
    void eshot_movement();
    bool eshot_trail(int n);
    void hit_check();
    bool game_pause;
    int i_border_colors;
    game_status_e game_status;
    map_info_t start_map;
    map_info_t map;
    vector<enemy_t> enemies;
    vector<shot_t> eshots;
    vector<battery_t> batteries;
    player_t player;
    chrono::duration<double> player_speed;
    chrono::high_resolution_clock::time_point clock_start1;
    chrono::high_resolution_clock::time_point clock_start2;
    chrono::high_resolution_clock::time_point clock_start3;
    chrono::high_resolution_clock::time_point clock_start4;
    direction_e direction;
    direction_e direction_register;
};

bool operator!=(position_t pos1, position_t pos2);
bool operator==(position_t pos1, position_t pos2);
bool operator!=(position_t pos, vector<enemy_t> enemies);

#endif /* !SOLARFOX_HPP_ */
