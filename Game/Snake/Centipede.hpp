/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** Centipede
*/

#ifndef CENTIPEDE_HPP_
#define CENTIPEDE_HPP_
#include "../IDisplayModule.hpp"

class Centipede : public IDisplayModule{
    public:
        Centipede();
        ~Centipede();
        void init();
        void stop();
        void update();
        const std::string &getName() const = 0;

    protected:
    private:
        std::string name;
        std::vector<std::string> map;
        int score;
};

#endif /* !CENTIPEDE_HPP_ */
