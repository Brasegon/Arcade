/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman()
{
    std::vector<std::string> n_map = {
        "XXXXXXXXXXXXXXXXXXXXX",
        "X.........X.........X",
        "X.XXX.XXX.X.XXX.XXX.X",
        "XoX X.X X.X.X X.X XoX",
        "X.XXX.XXX.X.XXX.XXX.X",
        "X...................X",
        "X.XXX.X.XXXXX.X.XXX.X",
        "X.XXX.X.XXXXX.X.XXX.X",
        "X.....X...X...X.....X",
        "XXXXX.XXX X XXX.XXXXX",
        "    X.X       X.X    ",
        "    X.X XX XX X.X    ",
        "XXXXX.X X   X X.XXXXX",
        "X    .  X   X  .    X",
        "XXXXX.X XXXXX X.XXXXX",
        "    X.X       X.X    ",
        "    X.X XXXXX X.X    ",
        "XXXXX.X XXXXX X.XXXXX",
        "X.........X.........X",
        "X.XXX.XXX.X.XXX.XXX.X",
        "Xo..X..... .....X..oX",
        "XXX.X.X.XXXXX.X.X.XXX",
        "XXX.X.X.XXXXX.X.X.XXX",
        "X.....X...X...X.....X",
        "X.XXXXXXX.X.XXXXXXX.X",
        "X...................X",
        "XXXXXXXXXXXXXXXXXXXXX"
    };
    name = "Pacaman";
    map = n_map;
    int score = 0;
    
}

void Pacman::init()
{

}

void Pacman::stop()
{

}

void Pacman::update()
{

}

const std::string &Pacman::getName() const
{
    return name;
}
const std::vector<std::string> &Pacman::getMap() const
{
    return map;
}

const std::vector<int> &Pacman::getPlayerPos() const
{
    return playerPos;
}

const int &Pacman::getScore() const
{
    return score;
}

Pacman::~Pacman()
{
}
