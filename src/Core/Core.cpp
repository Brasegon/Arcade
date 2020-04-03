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
    selected_game = 0;
    in_menu = true;
    game = nullptr;
    graph = nullptr;
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

void Core::load_lib()
{
    DLLoader<IGraphLib> *libtemp = new DLLoader<IGraphLib>(libList[selected_graph]);
    graph = libtemp->getInstance("entryPoint");
    DLLoader<game_lib> *gametemp = new DLLoader<game_lib>(gameList[selected_game]);
    game = gametemp->getInstance("entryPoint");
    if (graph == NULL)
        throw MyExeption("ALED");
    if (game == NULL)
        throw MyExeption("ALED2");
    graph->setGameList(gameList);
    graph->setLibList(libList);
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
        action = graph->getKey();
        mapinfo = game->game(action);
        graph->displayMap(mapinfo);
        if (action == PE_EXIT) {
            action = PE_NOACTION;
            in_menu = true;
            return;
        }
        if (event())
            return;
    }
}

void Core::arcade()
{
    if (in_menu)
        menu_loop();
    else
        game_loop();
}

bool Core::event()
{
    if (action == PE_EXIT
    || action == PE_NEXT_GAME
    || action == PE_PREV_GAME
    || action == PE_NEXT_LIB
    || action == PE_PREV_LIB)
        return true;
    return false;
}

void Core::nextGame_Lib()
{
    DLLoader<game_lib> *temp;

    if (gameList.size() == 1)
        return;
    selected_game++;
    if (selected_game > (int) gameList.size()-1)
        selected_game = 0;
    temp = new DLLoader<game_lib>(gameList[selected_game]);
    game = temp->getInstance("entryPoint", 40, 40);
    graph->init_game();
}

void Core::prevGame_Lib()
{
    if (gameList.size() == 1)
        return;
    selected_game--;
    if (selected_game < 0)
        selected_game = gameList.size()-1;
    DLLoader<game_lib> *temp = new DLLoader<game_lib>(gameList[selected_game]);
    game = temp->getInstance("entryPoint", 40, 40);
    graph->init_game();
}

void Core::nextGraphique_Lib()
{
    int max_graphical_lib = libList.size() - 1;
    selected_graph++;
    if (selected_graph > max_graphical_lib)
        selected_graph = 0;
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(libList[selected_graph]);
    graph = temp->getInstance("entryPoint");
    graph->init_game();
}

void Core::prevGraphique_Lib()
{
    int max_graphical_lib = libList.size() - 1;
    
    if (selected_graph == 0)
        selected_graph = max_graphical_lib;
    else
        selected_graph = selected_graph - 1;
    DLLoader<IGraphLib> *temp = new DLLoader<IGraphLib>(libList[selected_graph]);
    graph = temp->getInstance("entryPoint");
    graph->init_game();
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

Core::~Core()
{
}
