/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_
#include "../IDisplayModule.hpp"

class Pacman {
    public:
        Pacman();
        ~Pacman();
        void init();
        void stop();
        void update();
        const std::string &getName() const;
        const std::vector<std::string> &getMap() const;
        const std::vector<int> &getPlayerPos() const;
        const int &getScore() const;

    protected:
    private:
        std::string name;
        std::vector<std::string> map;
        int score;
        std::vector<int> playerPos;
};

#endif /* !PACMAN_HPP_ */
