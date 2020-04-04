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
#include <thread>
#include "MyExeption.hpp"
#include "../../Game/IGameLib.hpp"
#include "../../Lib/IGraphLib.hpp"
#include "DLLoader.hpp"

class Core {
    public:
        Core(const std::string &lib);
        ~Core();

        void load_lib();
        void arcade();
        bool event();
        void nextGame_Lib();
        void prevGame_Lib();
        void nextGraphique_Lib();
        void prevGraphique_Lib();
        void menu_loop();
        void game_loop();

        void parseGameList();
        const vector<string> &getGameList() const;
        
        void parseGraphList();
        const vector<string> &getLibList() const;

        playerEvent get_action() const;
    protected:
        IGraphLib *graph;
        game_lib *game;
        DLLoader<IGraphLib> *loaderGraph;
        DLLoader<game_lib> *loaderGame;
        int selected_game;
        int selected_graph;
        playerEvent action;
        bool in_menu;

        std::vector<std::string> libList;
        std::vector<std::string> gameList;
    private:
};

#endif /* !CORE_HPP_ */
