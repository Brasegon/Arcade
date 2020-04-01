/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** SolarFox
*/

#include "SolarFox.hpp"

SolarFox::SolarFox()
{
    srand(time(NULL));
    start_map.map = {
    "XXXXXXXXXXXXXXXXXXXXXXXX",
    "X4444444444444444444443X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  P  P  P  P  P  P  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  P  P  P  P  P  P  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  P  P  >  P  P  P  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  P  P  P  P  P  P  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  P  P  P  P  P  P  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  P  P  P  P  P  P  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XEYYYYYYYYYYYYYYYYYYYYYX",
    "XXXXXXXXXXXXXXXXXXXXXXXX",
    };
    reset_game();
}

SolarFox::~SolarFox()
{
}

void SolarFox::reset_game()
{
    //map generation
    game_pause = true;
    game_status = PLAYING;
    int id = 0;
    map = start_map;
    for (int a = 0; a < map.map.size(); a++) {
        for (int i = 0; i < map.map[a].size(); i++) {
            //init enemies
            if (map.map[a][i] == 'E' || map.map[a][i] == '3') {
                if (rand()%22 == 1) {
                    enemies.push_back({{i, a}, D_UP, 2, map.map[a][i]});
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            if (map.map[a][i] == '4' || map.map[a][i] == 'Y') {
                if (rand()%22 == 1) {
                    enemies.push_back({{i, a}, D_RIGHT, 2, map.map[a][i]});
                    map.map[a][i] = 'E';
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            //init batteries
            if (map.map[a][i] == 'P') {
                if (rand()%2 == 1) {
                    batteries.push_back({{i, a}, id++});
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            //init player
            if (map.map[a][i] == 'A') {
                player.pos = {i, a};
                player.direction = D_UP;
                player.shot = {{i, a}, 0, D_UP};
            }
            if (map.map[a][i] == 'V') {
                player.pos = {i, a};
                player.direction = D_DOWN;
                player.shot = {{i, a}, 0, D_DOWN};
            }
            if (map.map[a][i] == '<') {
                player.pos = {i, a};
                player.direction = D_LEFT;
                player.shot = {{i, a}, 0, D_LEFT};
            }
            if (map.map[a][i] == '>') {
                player.pos = {i, a};
                player.direction = D_RIGHT;
                player.shot = {{i, a}, 0, D_RIGHT};
            }
        }
    }
    clock_start1 = chrono::high_resolution_clock::now();
    clock_start2 = chrono::high_resolution_clock::now();
    clock_start3 = chrono::high_resolution_clock::now();
}

void SolarFox::enemies_movement()
{
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].life == 0) {
            continue;
        }
        if (enemies[i].direction == D_UP) {
            if (map.map[enemies[i].pos.y-1][enemies[i].pos.x] == 'X') {
                enemies[i].direction = D_DOWN;
                continue;
            }
            map.map[enemies[i].pos.y-1][enemies[i].pos.x] = enemies[i].symbol;
            map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.y--;
        }
        if (enemies[i].direction == D_DOWN) {
            if (map.map[enemies[i].pos.y+1][enemies[i].pos.x] == 'X') {
                enemies[i].direction = D_UP;
                continue;
            }
            map.map[enemies[i].pos.y+1][enemies[i].pos.x] = enemies[i].symbol;
            map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.y++;
        }
        if (enemies[i].direction == D_LEFT) {
            if (map.map[enemies[i].pos.y][enemies[i].pos.x-1] == 'X') {
                enemies[i].direction = D_RIGHT;
                continue;
            }
            map.map[enemies[i].pos.y][enemies[i].pos.x-1] = enemies[i].symbol;
            map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.x--;
        }
        if (enemies[i].direction == D_RIGHT) {
            if (map.map[enemies[i].pos.y][enemies[i].pos.x+1] == 'X') {
                enemies[i].direction = D_LEFT;
                continue;
            }
            map.map[enemies[i].pos.y][enemies[i].pos.x+1] = enemies[i].symbol;
            map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.x++;
        }
    }
    check_enemies_hitbox();
}

void SolarFox::player_movement()
{
    bool reg = true;
    direction = direction_register;
    switch (direction)
    {
    case D_UP:
        if (map.map[player.pos.y-1][player.pos.x] == 'X') {
            game_status = LOOSE;
        }
        if (map.map[player.pos.y-1][player.pos.x] == 'T') {
            reg = false;
        }
        break;
    case D_DOWN:
        if (map.map[player.pos.y+1][player.pos.x] == 'X') {
            game_status = LOOSE;
        }
        if (map.map[player.pos.y+1][player.pos.x] == 'T') {
            reg = false;
        }
        break;
    case D_LEFT:
        if (map.map[player.pos.y][player.pos.x-1] == 'X') {
            game_status = LOOSE;
        }
        if (map.map[player.pos.y][player.pos.x-1] == 'T') {
            reg = false;
        }
        break;
    case D_RIGHT:
        if (map.map[player.pos.y][player.pos.x+1] == 'X') {
            game_status = LOOSE;
        }
        if (map.map[player.pos.y][player.pos.x+1] == 'T') {
            reg = false;
        }
        break;
    default:
        break;
    }
    if (reg)
        player.direction = direction;
    switch (player.direction)
    {
    case D_UP:
        map.map[player.pos.y-1][player.pos.x] = 'A';
        map.map[player.pos.y][player.pos.x] = ' ';
        player.pos.y--;
        break;
    case D_DOWN:
        map.map[player.pos.y+1][player.pos.x] = 'V';
        map.map[player.pos.y][player.pos.x] = ' ';
        player.pos.y++;
        break;
    case D_LEFT:
        map.map[player.pos.y][player.pos.x-1] = '<';
        map.map[player.pos.y][player.pos.x] = ' ';
        player.pos.x--;
        break;
    case D_RIGHT:
        map.map[player.pos.y][player.pos.x+1] = '>';
        map.map[player.pos.y][player.pos.x] = ' ';
        player.pos.x++;
        break;
    default:
        break;
    }
    for (int i = 0; i < batteries.size(); i++) {
        if (batteries[i].pos == player.pos) {
            batteries.erase(batteries.begin()+i);
        }
    }
    if (batteries.empty()) {
        game_status = WIN;
        return;
    }
    check_enemies_hitbox();
}

void SolarFox::movement_register(playerEvent action)
{
    if (action == PE_UP && player.direction != D_DOWN) {
        direction_register = D_UP;
    }
    if (action == PE_DOWN && player.direction != D_UP) {
        direction_register = D_DOWN;
    }
    if (action == PE_LEFT && player.direction != D_RIGHT) {
        direction_register = D_LEFT;
    }
    if (action == PE_RIGHT && player.direction != D_LEFT) {
        direction_register = D_RIGHT;
    }
}

void SolarFox::check_enemies_hitbox()
{
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].pos == player.pos) {
            game_status = LOOSE;
            return;
        }
    }
}

void SolarFox::playershot_register(playerEvent action)
{
    if (action != PE_ACTION1)
        return;
    if (player.shot.distance != 0)
        return;
    if (player.direction == D_UP) {
        player.shot.pos = player.pos;
        player.shot.pos.y--;
        if (map.map[player.shot.pos.y][player.shot.pos.x] == 'X'
        ||map.map[player.shot.pos.y][player.shot.pos.x] == 'T')
            return;
        player.shot.distance = 1;
        player.shot.direction = D_UP;
        map.map[player.shot.pos.y][player.shot.pos.x] = 'o';
    }
    if (player.direction == D_DOWN) {
        player.shot.pos = player.pos;
        player.shot.pos.y++;
        if (map.map[player.shot.pos.y][player.shot.pos.x] == 'X'
        ||map.map[player.shot.pos.y][player.shot.pos.x] == 'T')
            return;
        player.shot.distance = 1;
        player.shot.direction = D_DOWN;
        map.map[player.shot.pos.y][player.shot.pos.x] = 'o';
    }
    if (player.direction == D_LEFT) {
        player.shot.pos = player.pos;
        player.shot.pos.x--;
        if (map.map[player.shot.pos.y][player.shot.pos.x] == 'X'
        ||map.map[player.shot.pos.y][player.shot.pos.x] == 'T')
            return;
        player.shot.distance = 1;
        player.shot.direction = D_LEFT;
        map.map[player.shot.pos.y][player.shot.pos.x] = 'o';
    }
    if (player.direction == D_RIGHT) {
        player.shot.pos = player.pos;
        player.shot.pos.x++;
        if (map.map[player.shot.pos.y][player.shot.pos.x] == 'X'
        ||map.map[player.shot.pos.y][player.shot.pos.x] == 'T')
            return;
        player.shot.distance = 1;
        player.shot.direction = D_RIGHT;
        map.map[player.shot.pos.y][player.shot.pos.x] = 'o';
    }
}

void SolarFox::pshot_movement()
{
    if (player.shot.distance == 0)
        return;
    map.map[player.shot.pos.y][player.shot.pos.x] = ' ';
    if (player.shot.direction == D_UP) {
        player.shot.pos.y--;
    }
    if (player.shot.direction == D_DOWN) {
        player.shot.pos.y++;
    }
    if (player.shot.direction == D_LEFT) {
        player.shot.pos.x--;
    }
    if (player.shot.direction == D_RIGHT) {
        player.shot.pos.x++;
    }
    for (int i = 0; i < batteries.size(); i++) {
        if (player.shot.pos == batteries[i].pos) {
            batteries.erase(batteries.begin()+i);
        }
    }
    player.shot.distance++;
    for (int i = 0; i < enemies.size(); i++) {
        if (player.shot.pos == enemies[i].pos) {
            enemies[i].life--;
            player.shot.distance = 0;
            return;
        }
    }
    if (player.shot.distance > 10
    || map.map[player.shot.pos.y][player.shot.pos.x] == 'X'
    || map.map[player.shot.pos.y][player.shot.pos.x] == 'T') {
        player.shot.distance = 0;
        return;
    }
    map.map[player.shot.pos.y][player.shot.pos.x] = 'o';
}

void SolarFox::enemies_check()
{
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].life <= 0) {
            enemies.erase(enemies.begin()+i);
            map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
        }
    }
}

map_info_t SolarFox::game(playerEvent action)
{
    chrono::high_resolution_clock::time_point clock_end;
    chrono::duration<double> elapsed_seconds;

    //pause
    if (game_pause) {
        if (action != PE_UP && action != PE_DOWN &&
            action != PE_LEFT && action != PE_RIGHT)
            return map;
        else
            game_pause = false;
    }
    clock_end = chrono::high_resolution_clock::now();
    //clock enemies
    elapsed_seconds = clock_end-clock_start1;
    if (elapsed_seconds > 0.25s) {
        enemies_movement();
        clock_start1 = chrono::high_resolution_clock::now();
    }
    movement_register(action);
    //clock player
    elapsed_seconds = clock_end-clock_start2;
    if (elapsed_seconds > 0.1s) {
        player_movement();
        clock_start2 = chrono::high_resolution_clock::now();
    }
    playershot_register(action);
    //clock playershot
    elapsed_seconds = clock_end-clock_start3;
    if (elapsed_seconds > 0.03s && player.shot.distance != 0) {
        pshot_movement();
        enemies_check();
        clock_start3 = chrono::high_resolution_clock::now();
    }
    if (game_status == LOOSE) {
        reset_game();
    }
    if (game_status == WIN) {
        reset_game();
    }
    return map;
}

/* ----------- operators ----------- */

bool operator!=(position_t pos1, position_t pos2)
{
    if (pos1.x != pos2.x || pos1.y != pos2.y) 
        return true;
    return false;
}

bool operator==(position_t pos1, position_t pos2)
{
    if (pos1.x == pos2.x && pos1.y == pos2.y) 
        return true;
    return false;
}