/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** SolarFox
*/

#include "SolarFox.hpp"

SolarFox::SolarFox()
{
    char c = 0;

    srand(time(NULL));
    start_map.map = {
    "XXXXXXXXXXXXXXXXXXXXXXXX",
    "X4444444444444444444443X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  B  B  B  B  B  B  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  B  B  B  B  B  B  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  B  B  >  B  B  B  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  B  B  B  B  B  B  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  B  B  B  B  B  B  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XE  B  B  B  B  B  B  3X",
    "XETT TT TT TT TT TT TT3X",
    "XETT TT TT TT TT TT TT3X",
    "XEYYYYYYYYYYYYYYYYYYYYYX",
    "XXXXXXXXXXXXXXXXXXXXXXXX",
    };
    start_map.score = 0;
    for (int y = 0; y < start_map.map.size(); y++) {
        for (int x = 0; x < start_map.map.size(); x++) {
            c = start_map.map[y][x];
            if (c == 'X') {
                start_map.pixel.push_back({BLACK, {x, y}});
            }
            if (c == 'T') {
                start_map.pixel.push_back({BLACK, {x, y}});
            }
        }
    }
    i_border_colors = start_map.pixel.size();
    reset_game();
}

SolarFox::~SolarFox()
{
}

void SolarFox::reset_game()
{
    //map generation
    if (!enemies.empty())
        enemies.clear();
    if (!batteries.empty())
        batteries.clear();
    if (!eshots.empty())
        eshots.clear();
    game_pause = true;
    game_status = PLAYING;
    map = start_map;
    direction = D_RIGHT;
    direction_register = D_RIGHT;
    player_speed = 0.1s;
    for (int a = 0; a < map.map.size(); a++) {
        for (int i = 0; i < map.map[a].size(); i++) {
            //init enemies
            if (map.map[a][i] == 'E') {
                if (rand()%22 == 1) {
                    enemies.push_back({{i, a}, D_UP, D_RIGHT, 2, 'E'});
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            if (map.map[a][i] == '3') {
                if (rand()%22 == 1) {
                    enemies.push_back({{i, a}, D_UP, D_LEFT, 2, 'E'});
                    map.map[a][i] = 'E';
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            if (map.map[a][i] == '4') {
                if (rand()%22 == 1) {
                    enemies.push_back({{i, a}, D_RIGHT, D_DOWN, 2, 'E'});
                    map.map[a][i] = 'E';
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            if (map.map[a][i] == 'Y') {
                if (rand()%22 == 1) {
                    enemies.push_back({{i, a}, D_RIGHT, D_UP, 2, 'E'});
                    map.map[a][i] = 'E';
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            //init batteries
            if (map.map[a][i] == 'B') {
                if (rand()%2 == 1) {
                    batteries.push_back({{i, a}});
                }
                else {
                    map.map[a][i] = ' ';
                }
            }
            //init player
            if (map.map[a][i] == '^') {
                player.pos = {i, a};
                player.direction = D_UP;
                player.shot = {{i, a}, 0, D_UP};
            }
            if (map.map[a][i] == 'v') {
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
    generate_path();
    generate_colors();
    clock_start1 = chrono::high_resolution_clock::now();
    clock_start2 = chrono::high_resolution_clock::now();
    clock_start3 = chrono::high_resolution_clock::now();
    clock_start4 = chrono::high_resolution_clock::now();
}

void SolarFox::generate_colors()
{
    char c = 0;

    if (map.pixel.size() > i_border_colors)
        map.pixel.erase(map.pixel.begin()+i_border_colors, map.pixel.end());
    for (int y = 0; y < map.map.size(); y++) {
        for (int x = 0; x < map.map.size(); x++) {
            c = map.map[y][x];
            // if (c == ' ') {
            //     map.pixel.push_back({WHITE, {x, y}});
            // }
            if (c == 'B') {
                map.pixel.push_back({YELLOW, {x, y}});
            }
            if (c == 'E') {
                map.pixel.push_back({MAGENTA, {x, y}});
            }
            if (c == '6') {
                map.pixel.push_back({RED, {x, y}});
            }
            if (c == 'o') {
                map.pixel.push_back({BLUE, {x, y}});
            }
            if (x == player.pos.x && y == player.pos.y) {
                map.pixel.push_back({GREEN, {x, y}});
            }
        }
    }
}

bool is_walkable(char c)
{
    if (c == 'X' || c == 'T')
        return false;
    return true;
}

void SolarFox::generate_path()
{
                    /*  + - / { } [ ] ( ) : ;  */
                    /*  ╋ ━ ┃ ┗ ┛ ┏ ┓ ┣ ┫ ┻ ┳  */
    char m;
    char u;
    char d;
    char l;
    char r;
    for (int y = 1; y < map.map.size()-1; y++) {
        for (int x = 1; x < map.map.size()-1; x++) {
            m = map.map[y][x];
            u = map.map[y-1][x];
            d = map.map[y+1][x];
            l = map.map[y][x-1];
            r = map.map[y][x+1];
            if (m == ' ') {
                if (is_walkable(u) && is_walkable(d) && is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = '+';
                    continue;
                }
                if (!is_walkable(u) && !is_walkable(d) && is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = '-';
                    continue;
                }
                if (is_walkable(u) && is_walkable(d) && !is_walkable(l) && !is_walkable(r)) {
                    map.map[y][x] = '/';
                    continue;
                }
                if (is_walkable(u) && !is_walkable(d) && !is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = '{';
                    continue;
                }
                if (is_walkable(u) && !is_walkable(d) && is_walkable(l) && !is_walkable(r)) {
                    map.map[y][x] = '}';
                    continue;
                }
                if (!is_walkable(u) && is_walkable(d) && !is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = '[';
                    continue;
                }
                if (!is_walkable(u) && is_walkable(d) && is_walkable(l) && !is_walkable(r)) {
                    map.map[y][x] = ']';
                    continue;
                }
                if (is_walkable(u) && is_walkable(d) && !is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = '(';
                    continue;
                }
                if (is_walkable(u) && is_walkable(d) && is_walkable(l) && !is_walkable(r)) {
                    map.map[y][x] = ')';
                    continue;
                }
                if (is_walkable(u) && !is_walkable(d) && is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = ':';
                    continue;
                }
                if (!is_walkable(u) && is_walkable(d) && is_walkable(l) && is_walkable(r)) {
                    map.map[y][x] = ';';
                    continue;
                }
            }
        }
    }
}

void SolarFox::check_batteries()
{
    char c = 0;
    for (int i = 0; i < batteries.size(); i++) {
        c = map.map[batteries[i].pos.y][batteries[i].pos.x];
        if (c != 'B' && c != '6')
            map.map[batteries[i].pos.y][batteries[i].pos.x] = 'B';
    }
}

bool SolarFox::enemy_trail(int n)
{
    for (int i = 0; i < enemies.size(); i++) {
        if (i == n)
            continue;
        if (enemies[i].pos == enemies[n].pos)
            return false;
    }
    return true;
}

void SolarFox::enemies_movement()
{
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].direction == D_UP) {
            if (map.map[enemies[i].pos.y-1][enemies[i].pos.x] == 'X') {
                enemies[i].direction = D_DOWN;
                continue;
            }
            map.map[enemies[i].pos.y-1][enemies[i].pos.x] = enemies[i].symbol;
            if (enemy_trail(i))
                map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.y--;
        }
        if (enemies[i].direction == D_DOWN) {
            if (map.map[enemies[i].pos.y+1][enemies[i].pos.x] == 'X') {
                enemies[i].direction = D_UP;
                continue;
            }
            map.map[enemies[i].pos.y+1][enemies[i].pos.x] = enemies[i].symbol;
            if (enemy_trail(i))
                map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.y++;
        }
        if (enemies[i].direction == D_LEFT) {
            if (map.map[enemies[i].pos.y][enemies[i].pos.x-1] == 'X') {
                enemies[i].direction = D_RIGHT;
                continue;
            }
            map.map[enemies[i].pos.y][enemies[i].pos.x-1] = enemies[i].symbol;
            if (enemy_trail(i))
                map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.x--;
        }
        if (enemies[i].direction == D_RIGHT) {
            if (map.map[enemies[i].pos.y][enemies[i].pos.x+1] == 'X') {
                enemies[i].direction = D_LEFT;
                continue;
            }
            map.map[enemies[i].pos.y][enemies[i].pos.x+1] = enemies[i].symbol;
            if (enemy_trail(i))
                map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies[i].pos.x++;
        }
        //tir random
        if (rand()%4 == 0) {
            if (enemies[i].canon_orientation == D_UP && map.map[enemies[i].pos.y-1][enemies[i].pos.x] != 'T') {
                eshots.push_back({{enemies[i].pos.x, enemies[i].pos.y-1}, 0, enemies[i].canon_orientation});
                map.map[eshots.back().pos.y][eshots.back().pos.x] = '6';
            }
            if (enemies[i].canon_orientation == D_DOWN && map.map[enemies[i].pos.y+1][enemies[i].pos.x] != 'T') {
                eshots.push_back({{enemies[i].pos.x, enemies[i].pos.y+1}, 0, enemies[i].canon_orientation});
                map.map[eshots.back().pos.y][eshots.back().pos.x] = '6';
            }
            if (enemies[i].canon_orientation == D_LEFT && map.map[enemies[i].pos.y][enemies[i].pos.x-1] != 'T') {
                eshots.push_back({{enemies[i].pos.x-1, enemies[i].pos.y}, 0, enemies[i].canon_orientation});
                map.map[eshots.back().pos.y][eshots.back().pos.x] = '6';
            }
            if (enemies[i].canon_orientation == D_RIGHT && map.map[enemies[i].pos.y][enemies[i].pos.x+1] != 'T') {
                eshots.push_back({{enemies[i].pos.x+1, enemies[i].pos.y}, 0, enemies[i].canon_orientation});
                map.map[eshots.back().pos.y][eshots.back().pos.x] = '6';
            }
        }
    }
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
        map.map[player.pos.y-1][player.pos.x] = '^';
        map.map[player.pos.y][player.pos.x] = ' ';
        player.pos.y--;
        break;
    case D_DOWN:
        map.map[player.pos.y+1][player.pos.x] = 'v';
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
            map.score += 1;
            i--;
        }
    }
    if (batteries.empty()) {
        game_status = WIN;
        return;
    }
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

void SolarFox::check_all_hitboxes()
{
    // enemies hitbox
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].pos == player.pos) {
            game_status = LOOSE;
            return;
        }
    }
    // enemies shots hitbox
    for (int i = 0; i < eshots.size(); i++) {
        if (eshots[i].pos == player.pos) {
            game_status = LOOSE;
            return;
        }
    }
    // playershot hitbox
    if (player.shot.distance > 0) {
        for (int i = 0; i < batteries.size(); i++) {
            if (player.shot.pos == batteries[i].pos) {
                batteries.erase(batteries.begin()+i);
                map.score += 1;
                i--;
            }
        }
        for (int i = 0; i < eshots.size(); i++) {
            if (player.shot.pos == eshots[i].pos) {
                eshots.erase(eshots.begin()+i);
                map.score += 1;
                i--;
            }
        }
        for (int i = 0; i < enemies.size(); i++) {
            if (player.shot.pos == enemies[i].pos) {
                enemies[i].life--;
                player.shot.distance = 0;
                return;
            }
        }
    }
}

void SolarFox::playershot_register(playerEvent action)
{
    if (action != PE_ACTION2)
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
    player.shot.distance++;
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
            map.map[enemies[i].pos.y][enemies[i].pos.x] = ' ';
            enemies.erase(enemies.begin()+i);
            map.score += 2;
            i--;
        }
    }
}

bool SolarFox::eshot_trail(int n)
{
    for (int i = 0; i < eshots.size(); i++) {
        if (i == n)
            continue;
        if (eshots[i].pos == eshots[n].pos)
            return false;
    }
    if (eshots[n].pos != enemies)
        return true;
    if (eshots[n].pos == player.pos)
        return false;
    return true;
}

void SolarFox::eshot_movement()
{
    for (int i = 0; i < eshots.size(); i++) {
        if (eshot_trail(i));
            map.map[eshots[i].pos.y][eshots[i].pos.x] = ' ';
        if (eshots[i].direction == D_UP) {
            eshots[i].pos.y--;
        }
        if (eshots[i].direction == D_DOWN) {
            eshots[i].pos.y++;
        }
        if (eshots[i].direction == D_LEFT) {
            eshots[i].pos.x--;
        }
        if (eshots[i].direction == D_RIGHT) {
            eshots[i].pos.x++;
        }
        if (map.map[eshots[i].pos.y][eshots[i].pos.x] == 'X') {
            eshots.erase(eshots.begin()+i);
            i--;
            continue;
        }
        map.map[eshots[i].pos.y][eshots[i].pos.x] = '6';
    }
}

map_info_t SolarFox::game(playerEvent action)
{
    chrono::high_resolution_clock::time_point clock_end;
    chrono::duration<double> elapsed_seconds;
    int score_register = 0;

    //restart
    if (action == PE_RESTART)
        reset_game();
    //pause
    if (game_pause) {
        if (action != PE_UP && action != PE_DOWN &&
            action != PE_LEFT && action != PE_RIGHT)
            return map;
        else
            game_pause = false;
    }
    //player acceleration
    if (action == PE_ACTION1) {
        if (player_speed == (chrono::duration<double>) 0.1s)
            player_speed = 0.06s;
        else
            player_speed = 0.1s;
    }
    check_batteries();
    enemies_check();
    clock_end = chrono::high_resolution_clock::now();
    //clock enemies
    elapsed_seconds = clock_end-clock_start1;
    if (elapsed_seconds > 0.25s) {
        enemies_movement();
        clock_start1 = chrono::high_resolution_clock::now();
    }
    check_all_hitboxes();
    movement_register(action);
    //clock player
    elapsed_seconds = clock_end-clock_start2;
    if (elapsed_seconds > player_speed) {
        player_movement();
        clock_start2 = chrono::high_resolution_clock::now();
    }
    check_all_hitboxes();
    playershot_register(action);
    //clock playershot
    elapsed_seconds = clock_end-clock_start3;
    if (elapsed_seconds > 0.03s && player.shot.distance != 0) {
        pshot_movement();
        clock_start3 = chrono::high_resolution_clock::now();
    }
    //clock enemiesshot
    elapsed_seconds = clock_end-clock_start4;
    if (elapsed_seconds > 0.1s) {
        eshot_movement();
        clock_start4 = chrono::high_resolution_clock::now();
    }
    check_all_hitboxes();
    if (game_status == LOOSE) {
        reset_game();
    }
    if (game_status == WIN) {
        score_register = map.score;
        reset_game();
        map.score = score_register;
    }
    generate_path();
    generate_colors();
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

bool operator!=(position_t pos, vector<enemy_t> enemies)
{
    for (int i = 0; i < enemies.size(); i++) {
        if (pos == enemies[i].pos)
            return false;
    }
    return true;
}
