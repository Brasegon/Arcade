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
    "XXXXXXXXXXXXXXXXXXXXXX"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X      OOOD          X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "X                    X"
    "XXXXXXXXXXXXXXXXXXXXXX"
    };
    // map = start_map;
    start_body[0] = {10, 10};
    start_body[1] = {10, 9};
    start_body[2] = {10, 8};
    start_body[3] = {10, 7};
    // body = start_body;
    apple.pos = {rand()%20+1, rand()%20+1};
    apple.eaten = false;
    direction = PE_RIGHT;
    clock_start = chrono::high_resolution_clock::now();
    game_pause = true;
}

Nibbler::~Nibbler()
{
}

map_info_t Nibbler::game(playerEvent action)
{
    chrono::high_resolution_clock::time_point clock_end;
    chrono::duration<double> elapsed_seconds;

    if (game_pause) {
        if (action == PE_NOACTION)
            return map;
        else
            game_pause = false;
    }
    clock_end = chrono::high_resolution_clock::now();
    elapsed_seconds = clock_end-clock_start;
    //next movement record
    if (action != PE_NOACTION) {
        direction = action;
    }
    //clock managment
    if (elapsed_seconds < 1s)
        return map;
    //apple generation
    if (apple.eaten) {
        apple.pos = {rand()%20+1, rand()%20+1};
        while(apple == body)
            apple.pos = {rand()%20+1, rand()%20+1};
        apple.eaten = false;
    }
    //movement
    if (move_body() == 1) {
        map = start_map;
        body = start_body;
        game_pause = true;
    }
    return map;
}

int Nibbler::move_body()
{
    if (direction == PE_UP) {
        //hitbox check
        if (map.map[body[0].y-1][body[0].x] == 'X')
            return 1;
        if (map.map[body[0].y-1][body[0].x] == 'P')
            apple.eaten = true;
        //move head
        map.map[body[0].y-1][body[0].x] = map.map[body[0].y][body[0].x];
        body[0].y--;
    }
    if (direction == PE_DOWN) {
        //hitbox check
        if (map.map[body[0].y+1][body[0].x] == 'X')
            return 1;
        if (map.map[body[0].y+1][body[0].x] == 'P')
            apple.eaten = true;
        //move head
        map.map[body[0].y+1][body[0].x] = map.map[body[0].y][body[0].x];
        body[0].y++;
    }
    if (direction == PE_LEFT) {
        //hitbox check
        if (map.map[body[0].y][body[0].x-1] == 'X')
            return 1;
        if (map.map[body[0].y][body[0].x-1] == 'P')
            apple.eaten = true;
        //move head
        map.map[body[0].y][body[0].x-1] = map.map[body[0].y][body[0].x];
        body[0].x--;
    }
    if (direction == PE_RIGHT) {
        //hitbox check
        if (map.map[body[0].y][body[0].x+1] == 'X')
            return 1;
        if (map.map[body[0].y][body[0].x+1] == 'P')
            apple.eaten = true;
        //move head
        map.map[body[0].y][body[0].x+1] = map.map[body[0].y][body[0].x];
        body[0].x++;
    }
    //hitbox check
    if (body[0] == body)
        return 1;
    //body following the head
    for (int i = 1; i < body.size(); i++) {
        map.map[body[i-1].y][body[i-1].x] = map.map[body[i].y][body[i].x];
        //replace the back case with nothing if no apple eaten
        if (i == body.size())
            if (apple.eaten) {
                body.push_back(body[i]);
                apple.eaten = false;
                break;
            }
            else
                map.map[body[i].y][body[i].x] = ' ';
        body[i].y = body[i-1].y;
        body[i].x = body[i-1].x;
    }
    return 0;
}

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