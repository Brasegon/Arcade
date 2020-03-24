/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <string>
#include <vector>
#include <dirent.h>
#include <regex>

class Core {
    public:
        Core(const std::string &lib);
        ~Core();

        void startArcade();

        void parseGameList();
        const std::vector<std::string> &getGameList() const;
        
        void parseGraphList();
        const std::vector<std::string> &getLibList() const;

    protected:
        const std::string libName;
        std::vector<std::string> libList;
        std::vector<std::string> gameList;
    private:
};

#endif /* !CORE_HPP_ */
