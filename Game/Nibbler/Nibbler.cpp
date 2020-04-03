/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    srand(time(NULL));
    start_map.map = {
    "XXXXXXXXXXXXXXXXXXXXXX",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X      OOO>          X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "X                    X",
    "XXXXXXXXXXXXXXXXXXXXXX",
    };
    start_map.score = 0;
    start_body = {
        {10, 10},
        {9, 10},
        {8, 10},
        {7, 10},
    };
    reset_game();
}

Nibbler::~Nibbler()
{
}

void Nibbler::reset_game()
{
    map = start_map;
    body = start_body;
    generate_apple();
    generate_colors();
    game_pause = true;
    direction_register = PE_RIGHT;
    direction = PE_RIGHT;
    apple.eaten = false;
    game_speed = 0.2s;
    clock_start = chrono::high_resolution_clock::now();
}

void Nibbler::generate_colors()
{
    char c = 0;

    map.pixel.clear();
    for (int y = 0; y < map.map.size(); y++) {
        for (int x = 0; x < map.map.size(); x++) {
            c = map.map[y][x];
            if (c == 'X') {
                map.pixel.push_back({WHITE, {x, y}});
            }
            if (c == 'P') {
                map.pixel.push_back({RED, {x, y}});
            }
            if (c == 'O') {
                map.pixel.push_back({GREEN, {x, y}});
            }
            if (c == '<' || c == '>' || c == '^' || c == 'v') {
                map.pixel.push_back({GREEN, {x, y}});
            }
        }
    }
}


void Nibbler::generate_apple()
{
    position_t previous_pos = apple.pos;
    apple.pos = {rand()%20+1, rand()%20+1};
    while(apple == body && apple.pos != previous_pos)
        apple.pos = {rand()%20+1, rand()%20+1};
    map.map[apple.pos.y][apple.pos.x] = 'P';
}


map_info_t Nibbler::game(playerEvent action)
{
    chrono::high_resolution_clock::time_point clock_end;
    chrono::duration<double> elapsed_seconds;

    if (game_pause) {
        if (action != PE_UP && action != PE_DOWN &&
            action != PE_LEFT && action != PE_RIGHT)
            return map;
        else
            game_pause = false;
    }
    //next movement record
    if (action == PE_UP || action == PE_DOWN ||
        action == PE_LEFT || action == PE_RIGHT) {
        if (action == PE_UP && direction != PE_DOWN)
            direction_register = action;
        if (action == PE_DOWN && direction != PE_UP)
            direction_register = action;
        if (action == PE_LEFT && direction != PE_RIGHT)
            direction_register = action;
        if (action == PE_RIGHT && direction != PE_LEFT)
            direction_register = action;
    }
    //player acceleration
    if (action == PE_ACTION1) {
        if (game_speed == (chrono::duration<double>) 0.2s)
            game_speed = 0.1s;
        else
            game_speed = 0.2s;
    }
    clock_end = chrono::high_resolution_clock::now();
    elapsed_seconds = clock_end-clock_start;
    if (elapsed_seconds < game_speed)
        return map;
    clock_start = chrono::high_resolution_clock::now();
    //movement
    if (move_body() == 1) {
        reset_game();
    }
    //color
    generate_colors();
    return map;
}

int Nibbler::move_body()
{
    direction = direction_register;
    if (direction == PE_UP) {
        if ((position_t){body[0].x, body[0].y-1} == apple.pos) {
            generate_apple();
            apple.eaten = true;
            map.score += 1;
        }
    }
    if (direction == PE_DOWN) {
        if ((position_t){body[0].x, body[0].y+1} == apple.pos) {
            generate_apple();
            apple.eaten = true;
            map.score += 1;
        }
    }
    if (direction == PE_LEFT) {
        if ((position_t){body[0].x-1, body[0].y} == apple.pos) {
            generate_apple();
            apple.eaten = true;
            map.score += 1;
        }
    }
    if (direction == PE_RIGHT) {
        if ((position_t){body[0].x+1, body[0].y} == apple.pos) {
            generate_apple();
            apple.eaten = true;
            map.score += 1;
        }
    }
    // body following the head
    for (int i = body.size()-1; i > 0; i--) {
        map.map[body[i-1].y].at(body[i-1].x) = 'O';
        //replace the back case with nothing if no apple eaten
        if (i == body.size()-1) {
            if (apple.eaten) {
                //snake body + 1
                body.push_back(body[i]);
                apple.eaten = false;
            }
            else
                map.map[body[i].y][body[i].x] = ' ';
        }
        body[i].y = body[i-1].y;
        body[i].x = body[i-1].x;
    }
    if (direction == PE_UP) {
        //hitbox check
        if (map.map[body[0].y-1][body[0].x] == 'X')
            return 1;
        map.map[body[0].y-1][body[0].x] = '^';
        body[0].y--;
    }
    if (direction == PE_DOWN) {
        //hitbox check
        if (map.map[body[0].y+1][body[0].x] == 'X')
            return 1;
        //move head
        map.map[body[0].y+1][body[0].x] = 'v';
        body[0].y++;
    }
    if (direction == PE_LEFT) {
        //hitbox check
        if (map.map[body[0].y][body[0].x-1] == 'X')
            return 1;
        //move head
        map.map[body[0].y][body[0].x-1] = '<';
        body[0].x = body[0].x - 1;
    }
    if (direction == PE_RIGHT) {
        //hitbox check
        if (map.map[body[0].y][body[0].x+1] == 'X')
            return 1;
        //move head
        map.map[body[0].y][body[0].x+1] = '>';
        body[0].x = body[0].x + 1;
    }
    //hitbox check
    if (body[0] == body)
        return 1;
    return 0;
}

/* ----------- operators ----------- */

//check if the apple appeared on an occupied case
bool operator==(apple_t apple, vector<position_t> vect)
{
    for (position_t vpos : vect) {
        if (apple.pos.x == vpos.x  && apple.pos.y == vpos.y)
            return true;
    }
    return false;
}

//check if the head collided with the body
bool operator==(position_t pos, vector<position_t> vect)
{
    for (int i = 0; i < vect.size(); i++) {
        if (i == 0)
            continue;
        if (pos.x == vect[i].x  && pos.y == vect[i].y)
            return true;
    }
    return false;
}

bool operator==(position_t pos1, position_t pos2)
{
    if (pos1.x == pos2.x && pos1.y == pos2.y) 
        return true;
    return false;
}

//check if the apple is generated on the same case
bool operator!=(position_t pos1, position_t pos2)
{
    if (pos1.x != pos2.x || pos1.y != pos2.y) 
        return true;
    return false;
}