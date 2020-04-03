/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** main
*/
#include <string>
#include <fstream>
#include <iostream>
#include "src/Core/Core.hpp"
using namespace std;
static const string HELP_MESSAGE = "BINARY NAME :\n"
	"\tarcade\n"
	"\nUSAGE :\n"
	"\t./arcade [path]\n"
	"\n\tpath : Path to a graphic lib to start the arcade bin.\n"
	"\tThe file should be a .so file.\n"
	"\nDESCRIPTION :\n"
	"\tThe arcade project has the purpose to "
	"load with any graphical lib in C++\n"
	"\tany game that you can find in the /games folder.\n"
	"\n\tin the /libs folder, you will find the libs loadable"
	" by the arcade project.\n"
	"\tin the /games folder, the games you can play with "
	"any loadable lib.\n"
	"\nABOUT :\n"
	"\tFor more information, see the documentation of "
	"the project in the folder.\n";

void checkFileExist(char *file) {
    std::ifstream lib(file);

    if (!lib || lib.fail()) {
        cout << HELP_MESSAGE << endl;
        exit(84);
    }
}

template<typename K>
void print_vector(vector<K> const &m)
{
    for (auto const& pair: m) {
        cout << pair << endl;
    }
}

int main(int ac, char **av)
{
    if (ac == 2) {
        checkFileExist(av[1]);
        Core core(av[1]);
        try {
            core.load_lib();
            while (core.get_action() != PE_EXIT) {
                core.arcade();
                if (core.get_action() == PE_NEXT_GAME)
                    core.nextGame_Lib();
                if (core.get_action() == PE_PREV_GAME)
                    core.prevGame_Lib();
                if (core.get_action() == PE_NEXT_LIB)
                    core.nextGraphique_Lib();
                if (core.get_action() == PE_PREV_LIB)
                    core.prevGraphique_Lib();
            }
        }
        catch (MyExeption &e) {
            printf("exception : %s", e.what());
            return 84;
        }
        return (0);
    }
    return (84);
}