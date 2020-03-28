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
    _what_game = 0;
    _actual_game_lib = nullptr;
    _actual_graphical_lib = nullptr;
    // libList.push_back(lib);
    parseGameList();
    parseGraphList();
}

std::string const &Core::getPathGameFromWhatGame()
{
    int x = 0;
    std::map<std::string, std::string>::iterator i = _map_game_path.begin();

    while (i != _map_game_path.end() && x != _what_game) {
        x++;
        i++;
    }
    return (i->second);
}

std::string const &Core::getPathLibFromWhatLib()
{
     return (libList[_what_game]);
}

void Core::load_lib()
{
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(getPathLibFromWhatLib());
    _actual_graphical_lib = temp->getInstance("entryPoint");
    if (_actual_graphical_lib == NULL)
        throw MyExeption("ALED");
    startArcade();
}

void Core::startArcade() {
    // if (_actual_graphical_lib->menu() == 1)
    //     _what_game = 1;
    // else
    //     _what_game = 0;
    // if (_actual_game_lib != NULL)
    //     delete _actual_game_lib;
    // DLLoader<IGame_lib> *temp = new DLLoader<IGame_lib>(getPathGameFromWhatGame());
    // _actual_game_lib = temp->getInstance("game", 40, 40);
    // if (_actual_game_lib == NULL)
    //     throw MyExeption("actual_game_lib == NULL");
    startGame();
}

void Core::restartArcade() {
    if (_actual_game_lib != NULL)
        delete _actual_game_lib;
    DLLoader<IGame_lib> *temp = new DLLoader<IGame_lib>(getPathGameFromWhatGame());
    _actual_game_lib = temp->getInstance("game", 40, 40);
    if (_actual_game_lib == NULL)
        throw MyExeption("actual_game_lib == NULL");
    startGame();
}

void menu_loop(IGame_lib *game, IGraphLib *lib)
{
    int ret;

    lib->init_menu();
    while (1) {
        ret = lib->displayMenu();
        if (ret == -1)
            return;
        if (ret == 1) {
            game_loop(game, lib);
            return;
        }
    }
}

void game_loop(IGame_lib *game, IGraphLib *lib)
{
    int key;
    map_info_t mapinfo;

    lib->init_game();
    while (1) {
        // mapinfo.map = game->getMap();
        // lib->displayMap(mapinfo);
        key = lib->getKey();
        // event(key);
        if (key == 'q')
            return;
        if (key == 'm') {
            menu_loop(game, lib);
            return;
        }
    }
}

void Core::startGame()
{
    _actual_graphical_lib->setGameList(gameList);
    _actual_graphical_lib->setLibList(libList);
    menu_loop(_actual_game_lib, _actual_graphical_lib);
    delete _actual_graphical_lib;
}

void Core::event(int record_key) /* A completer surment avec un enum pour facilitée la comprension */
{
    if (record_key == keyEvent::NEXT_GAME)
        nextGame_Lib();
    if (record_key == keyEvent::PREV_GAME)
        prevGame_Lib();
    if (record_key == keyEvent::NEXT_LIB)
        nextGraphique_Lib();
    if (record_key == keyEvent::PREV_LIB)
        prevGraphique_Lib();
    if (record_key == keyEvent::RESTART)
        restartArcade();
    if (record_key == keyEvent::START)
        startGame();
}

void Core::drawGame_Map()
{

}

void Core::nextGame_Lib()
{
    int max_game_lib = _map_game_path.size() - 1;

    _what_game = _what_game + 1;
    if (_what_game > max_game_lib)
        _what_game = 0;
    DLLoader<IGame_lib> *temp = new DLLoader<IGame_lib>(getPathGameFromWhatGame());
    if (_actual_game_lib != NULL)
        delete _actual_game_lib;
    _actual_game_lib = temp->getInstance("Game", 40, 40);
    _map = _actual_game_lib->getMap();
}

void Core::prevGame_Lib()
{
    int max_game_lib = _map_game_path.size() - 1;

    if (_what_game == 0)
        _what_game = max_game_lib;
    else _what_game = _what_game - 1;
    DLLoader<IGame_lib> *temp = new DLLoader<IGame_lib>(getPathGameFromWhatGame());
    delete _actual_game_lib;
    _actual_game_lib = temp->getInstance("Game", 40, 40);
    _map = _actual_game_lib->getMap();
}

void Core::nextGraphique_Lib()
{
    int max_graphical_lib = libList.size() - 1;
    
    _what_graphical_lib = _what_graphical_lib + 1;
    if (_what_graphical_lib > max_graphical_lib)
        _what_graphical_lib = 0;
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(getPathLibFromWhatLib());
    delete _actual_graphical_lib;
    _actual_graphical_lib = temp->getInstance("graphical_lib");
}

void Core::prevGraphique_Lib()
{
    int max_graphical_lib = libList.size() - 1;
    
    if (_what_graphical_lib == 0)
        _what_graphical_lib = max_graphical_lib;
    else
        _what_graphical_lib = _what_graphical_lib - 1;
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(getPathLibFromWhatLib());
    delete _actual_graphical_lib;
    _actual_graphical_lib = temp->getInstance("graphical_lib");
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
                _map_game_path[name] = "./Game/" + name;
                // gameList.push_back("./Game/" + name);
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

Core::~Core()
{
}
