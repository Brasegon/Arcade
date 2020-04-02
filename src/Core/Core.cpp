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
    libList.insert(libList.begin(), "./" + lib);
    parseGameList();
    parseGraphList();
}

std::string const &Core::getPathGameFromWhatGame()
{
     return (gameList[_what_game]);
}

std::string const &Core::getPathLibFromWhatLib()
{
     return (libList[_what_graphical_lib]);
}

void Core::load_lib()
{
    DLLoader<IGraphLib> *libtemp = new DLLoader<IGraphLib>(getPathLibFromWhatLib());
    _actual_graphical_lib = libtemp->getInstance("entryPoint");
    DLLoader<game_lib> *gametemp = new DLLoader<game_lib>(getPathGameFromWhatGame());
    _actual_game_lib = gametemp->getInstance("entryPoint");
    if (_actual_graphical_lib == NULL)
        throw MyExeption("ALED");
    if (_actual_game_lib == NULL)
        throw MyExeption("ALED2");
    startArcade();
}

void Core::startArcade() {
    // if (_actual_graphical_lib->menu() == 1)
    //     _what_game = 1;
    // else
    //     _what_game = 0;
    // if (_actual_game_lib != NULL)
    //     delete _actual_game_lib;
    // DLLoader<game_lib> *temp = new DLLoader<game_lib>(getPathGameFromWhatGame());
    // _actual_game_lib = temp->getInstance("game", 40, 40);
    // if (_actual_game_lib == NULL)
    //     throw MyExeption("actual_game_lib == NULL");
    startGame();
}

void Core::restartArcade() {
    if (_actual_game_lib != NULL)
        delete _actual_game_lib;
    DLLoader<game_lib> *temp = new DLLoader<game_lib>(getPathGameFromWhatGame());
    _actual_game_lib = temp->getInstance("game", 40, 40);
    if (_actual_game_lib == NULL)
        throw MyExeption("actual_game_lib == NULL");
    startGame();
}

void Core::menu_loop()
{
    int ret;

    std::vector<string> libs;
    map<string, string>::iterator it;

    _actual_graphical_lib->setLibList(libList);
    _actual_graphical_lib->init_menu();

    while (1) {
        ret = _actual_graphical_lib->displayMenu();
        // std::cout << ret << std::endl;
        if (ret == -1) {
            exit(0);
        }
        if (ret == 1) {
            // _what_game = 0;
            // if (_actual_game_lib != NULL)
            //     delete _actual_game_lib;
            // DLLoader<game_lib> *temp = new DLLoader<game_lib>(getPathGameFromWhatGame());
            // _actual_game_lib = temp->getInstance("game", 40, 40);
            game_loop();
            return;
        }
        if (ret == 2) {
            // _what_game = 1;
            // if (_actual_game_lib != NULL)
            //     delete _actual_game_lib;
            // DLLoader<game_lib> *temp = new DLLoader<game_lib>(getPathGameFromWhatGame());
            // _actual_game_lib = temp->getInstance("game", 40, 40);
            game_loop();
            return;
        }
    }
}

void Core::game_loop()
{
    playerEvent action = PE_NOACTION;
    map_info_t mapinfo;
    
    _actual_graphical_lib->init_game();
    while (1) {
        action = _actual_graphical_lib->getKey();
        event(action);
        mapinfo = _actual_game_lib->game(action);
        _actual_graphical_lib->displayMap(mapinfo);
        if (action == PE_EXIT) {
            return;
        }
        if (action == PE_RESTART) {
            menu_loop();
            return;
        }
    }
}

void Core::startGame()
{
    _actual_graphical_lib->setGameList(gameList);
    _actual_graphical_lib->setLibList(libList);
    menu_loop();
}

void Core::event(playerEvent record_key)
{
    if (record_key == PE_NEXT_GAME)
        nextGame_Lib();
    if (record_key == PE_PREV_GAME)
        prevGame_Lib();
    if (record_key == PE_NEXT_LIB) {
        nextGraphique_Lib();
        
    }
    if (record_key == PE_PREV_LIB)
        prevGraphique_Lib();
    // if (record_key == PE_RESTART)
    //     restartArcade();
}

// void Core::drawGame_Map()
// {
// 
// }

void Core::nextGame_Lib()
{
    int max_game_lib = gameList.size() - 1;
    _what_game = _what_game + 1;
    if (_what_game > max_game_lib)
        _what_game = 0;
    DLLoader<game_lib> *temp = new DLLoader<game_lib>(getPathGameFromWhatGame());
    // if (_actual_game_lib != NULL)
    //     delete _actual_game_lib;
    _actual_game_lib = temp->getInstance("entryPoint", 40, 40);
    _actual_graphical_lib->init_game();
}

void Core::prevGame_Lib()
{
    int max_game_lib = gameList.size() - 1;

    if (_what_game == 0)
        _what_game = max_game_lib;
    else _what_game = _what_game - 1;
    DLLoader<game_lib> *temp = new DLLoader<game_lib>(getPathGameFromWhatGame());
    _actual_game_lib = temp->getInstance("entryPoint", 40, 40);
    _actual_graphical_lib->init_game();
}

void Core::nextGraphique_Lib()
{
    int max_graphical_lib = libList.size() - 1;
    _what_graphical_lib = _what_graphical_lib + 1;
    if (_what_graphical_lib > max_graphical_lib)
        _what_graphical_lib = 0;
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(getPathLibFromWhatLib());
    _actual_graphical_lib = temp->getInstance("entryPoint");
    _actual_graphical_lib->init_game();
}

void Core::prevGraphique_Lib()
{
    //delete _actual_graphical_lib;
    int max_graphical_lib = libList.size() - 1;
    
    if (_what_graphical_lib == 0)
        _what_graphical_lib = max_graphical_lib;
    else
        _what_graphical_lib = _what_graphical_lib - 1;
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(getPathLibFromWhatLib());
    _actual_graphical_lib = temp->getInstance("entryPoint");
    _actual_graphical_lib->init_game();
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
                printf("%s", name.c_str());
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
