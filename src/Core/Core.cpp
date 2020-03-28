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
    int x = 0;
    std::map<std::string, std::string>::iterator i = _map_lib_path.begin();

    while (i != _map_lib_path.end() && x != _what_graphical_lib) {
        x++;
        i++;
    }
    return (i->second);
}

void Core::load_lib()
{
    DLLoader<IGraphical_lib> *temp = new DLLoader<IGraphical_lib>(getPathLibFromWhatLib());

    _actual_graphical_lib = temp->getInstance("graphical_lib");
    if (_actual_graphical_lib == NULL)
        throw MyExeption("ALED");
    startArcade();
}

void Core::startArcade() {
    if (_actual_graphical_lib->menu() == 1)
        _what_game = 1;
    else
        _what_game = 0;
    if (_actual_game_lib != NULL)
        delete _actual_game_lib;
    DLLoader<IGame_lib> *temp = new DLLoader<IGame_lib>(getPathGameFromWhatGame());
    _actual_game_lib = temp->getInstance("game", 40, 40);
    if (_actual_game_lib == NULL)
        throw MyExeption("actual_game_lib == NULL");
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

void Core::startGame()
{
    int record_key = 0;
    _map = _actual_game_lib->getMap();

    while (1) /* Manque d'une condition de fin de jeux */
    {
        _actual_graphical_lib->clear(); /* Clear l'affichage */
        drawGame_Map(); /* Draw map */
        record_key = _actual_graphical_lib->getKey(); /* recuper les imput du clavier */
        if (record_key == -1)
            exit(0);
        if (record_key != 0)
            event(record_key);
    }
}

void Core::event(int record_key) /* A completer surment avec un enum pour facilitée la comprension */
{
    if (record_key == 1)
        nextGame_Lib();
    if (record_key == 2)
        prevGame_Lib();
    if (record_key == 3)
        nextGraphique_Lib();
    if (record_key == 4)
        prevGraphique_Lib();
    if (record_key == 5)
        restartArcade();
    if (record_key == 6)
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
    int max_graphical_lib = _map_lib_path.size() - 1;
    
    _what_graphical_lib = _what_graphical_lib + 1;
    if (_what_graphical_lib > max_graphical_lib)
        _what_graphical_lib = 0;
    DLLoader<IGraphical_lib> *temp = new DLLoader<IGraphical_lib>(getPathLibFromWhatLib());
    delete _actual_graphical_lib;
    _actual_graphical_lib = temp->getInstance("graphical_lib");
}

void Core::prevGraphique_Lib()
{
    int max_graphical_lib = _map_lib_path.size() - 1;
    
    if (_what_graphical_lib == 0)
        _what_graphical_lib = max_graphical_lib;
    else
        _what_graphical_lib = _what_graphical_lib - 1;
    DLLoader<IGraphical_lib> *temp = new DLLoader<IGraphical_lib>(getPathLibFromWhatLib());
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
            if (std::regex_match(name.c_str(), cm, REGEX) /*&& std::find(libList.begin(), libList.end(), "./Lib/" + name) == libList.end()*/) {
                _map_lib_path[name] = "./Lib/" + name;
                // libList.push_back("./Lib/" + name);
            }
            free(namelist[n]);
        }
        free(namelist);
    }
}

const std::map<std::string, std::string> &Core::getGameList() const {
    return _map_game_path;
}

const std::map<std::string, std::string> &Core::getLibList() const {
    return _map_lib_path;
}

Core::~Core()
{
}
