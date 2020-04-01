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
#include "MyExeption.hpp"
#include "../../Game/IGameLib.hpp"
#include "../../Lib/IGraphLib.hpp"

class Core {
    public:
        Core(const std::string &lib);
        ~Core();

        void load_lib();
        std::string const &getPathGameFromWhatGame();
        std::string const &getPathLibFromWhatLib();
        void startArcade();
        void restartArcade();
        void startGame();
        void event(playerEvent record_key);
        // void drawGame_Map();
        void nextGame_Lib();
        void prevGame_Lib();
        void nextGraphique_Lib();
        void prevGraphique_Lib();
        void menu_loop();
        void game_loop();

        void parseGameList();
        const std::map<std::string, std::string> &getGameList() const;
        
        void parseGraphList();
        const std::map<std::string, std::string> &getLibList() const;

    protected:
        std::map<std::string, std::string> _map_lib_path;
        std::map<std::string, std::string> _map_game_path;
        std::string _string_path_lib;
        IGraphLib *_actual_graphical_lib;
        game_lib *_actual_game_lib;
        int _what_game;
        int _what_graphical_lib;
        /*map_info_t*/ std::vector<std::string> _map;


        const std::string libName;
        std::vector<std::string> libList;
        std::vector<std::string> gameList;
    private:
};

#endif /* !CORE_HPP_ */
