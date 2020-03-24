/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** Core
*/

#include "Core.hpp"
#include "DLLoader.hpp"

static const std::regex REGEX("^[a-zA-Z0-9_]*.so");
Core::Core(const std::string &lib)
{
    // libList.push_back(lib);
    parseGameList();
    parseGraphList();
}

void Core::startArcade() {
    
}

void Core::parseGameList() {
    struct dirent **namelist;
    int n = scandir("./Game", &namelist, 0, alphasort);

    if (n < 0)
        perror("scandir");
    else {
        while(n--) {
            std::cmatch cm;
		    std::string name = namelist[n]->d_name;
            if (std::regex_match(name.c_str(), cm, REGEX)) {
                gameList.push_back("./Game/" + name);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
}

void Core::parseGraphList() {
    struct dirent **namelist;
    int n = scandir("./Lib", &namelist, 0, alphasort);

    if (n < 0)
        perror("scandir");
    else {
        while(n--) {
            std::cmatch cm;
		    std::string name = namelist[n]->d_name;
            if (std::regex_match(name.c_str(), cm, REGEX) && std::find(libList.begin(), libList.end(), "./Lib/" + name) == libList.end()) {
                libList.push_back("./Lib/" + name);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
}

const std::vector<std::string> &Core::getGameList() const {
    return gameList;
}

const std::vector<std::string> &Core::getLibList() const {
    return libList;
}

Core::~Core()
{
}
