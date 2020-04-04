/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** Core
*/

#include "Core.hpp"
#include "fstream"

static const std::regex REGEX("^[a-zA-Z0-9_]*.so");

Core::Core(const std::string &lib)
{
    selected_game = 0;
    in_menu = true;
    game = nullptr;
    graph = nullptr;
    loaderGraph = nullptr;
    loaderGame = nullptr;
    action = PE_NOACTION;
    selected_graph = 0;
    selected_game = 0;
    if (lib.find("./Lib") == 0)
        libList.insert(libList.begin(), lib);
    else
        libList.insert(libList.begin(), "./" + lib);
    parseGameList();
    parseGraphList();
    if (gameList.empty() || libList.empty())
        action = PE_EXIT;
}

Core::~Core()
{
    if (loaderGraph != nullptr)
        delete loaderGraph;
    if (loaderGame != nullptr)
        delete loaderGame;
}

void Core::load_lib()
{
    if (loaderGraph != nullptr)
        delete loaderGraph;
    if (loaderGame != nullptr)
        delete loaderGame;
    loaderGraph = new DLLoader<IGraphLib>(libList[selected_graph]);
    graph = loaderGraph->getInstance();
    loaderGame = new DLLoader<game_lib>(gameList[selected_game]);
    game = loaderGame->getInstance();
    if (graph == NULL)
        throw MyExeption("failed to load graphical library");
    if (game == NULL)
        throw MyExeption("failed to load game library");
    graph->setGameList(gameList);
    graph->setLibList(libList);
}


void Core::arcade()
{
    if (in_menu) {
        menu_loop();
    }
    else {
        game_loop();
    }
}

void Core::menu_loop()
{
    graph->init_menu();
    while (1) {
        action = graph->displayMenu();
        if (action == PE_RESTART) {
            in_menu = false;
            return;
        }
        if (event())
            return;
    }
}

void Core::game_loop()
{
    map_info_t mapinfo;

    graph->init_game();
    while (1) {
        mapinfo = game->game(action);
        graph->displayMap(mapinfo);
        action = graph->getKey();
        if (action == PE_EXIT) {
            action = PE_NOACTION;
            in_menu = true;
            return;
        }
        if (event())
            return;
    }
}

bool Core::event()
{
    if (action == PE_NEXT_GAME) {
        nextGame_Lib();
        return true;
    }
    if (action == PE_PREV_GAME) {
        prevGame_Lib();
        return true;
    }
    if (action == PE_NEXT_LIB) {
        nextGraphique_Lib();
        return true;
    }
    if (action == PE_PREV_LIB) {
        prevGraphique_Lib();
        return true;
    }
    if (action == PE_EXIT) {
        return true;
    }
    return false;
}

void Core::nextGame_Lib()
{
    if (gameList.size() == 1)
        return;
    delete loaderGame;
    selected_game++;
    if (selected_game > (int) gameList.size()-1)
        selected_game = 0;
    loaderGame = new DLLoader<game_lib>(gameList[selected_game]);
    game = loaderGame->getInstance();
    if (game == NULL)
        throw MyExeption("failed to load game library");
}

void Core::prevGame_Lib()
{
    if (gameList.size() == 1)
        return;
    delete loaderGame;
    selected_game--;
    if (selected_game < 0)
        selected_game = gameList.size()-1;
    loaderGame = new DLLoader<game_lib>(gameList[selected_game]);
    game = loaderGame->getInstance();
    if (game == NULL)
        throw MyExeption("failed to load game library");
}

void Core::nextGraphique_Lib()
{
    if (libList.size() == 1)
        return;
    delete loaderGraph;
    selected_graph++;
    if (selected_graph > (int) libList.size()-1)
        selected_graph = 0;
    loaderGraph = new DLLoader<IGraphLib>(libList[selected_graph]);
    graph = loaderGraph->getInstance();
    if (graph == NULL)
        throw MyExeption("failed to load graphical library");
    graph->setGameList(gameList);
    graph->setLibList(libList);
}

void Core::prevGraphique_Lib()
{
    if (libList.size() == 1)
        return;
    delete loaderGraph;
    selected_graph--;
    if (selected_graph < 0)
        selected_graph = libList.size()-1;
    loaderGraph = new DLLoader<IGraphLib>(libList[selected_graph]);
    graph = loaderGraph->getInstance();
    if (graph == NULL)
        throw MyExeption("failed to load graphical library");
    graph->setGameList(gameList);
    graph->setLibList(libList);
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
                printf("%s\n", name.c_str());
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

const vector<string> &Core::getGameList() const
{
    return gameList;
}

const vector<string> &Core::getLibList() const
{
    return libList;
}

playerEvent Core::get_action() const
{
    return action;
}

