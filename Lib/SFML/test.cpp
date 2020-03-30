#include "SFML.hpp"

int main()
{
    SFML test;
    test.init_menu();
    while (1) {
        test.displayMenu();
    }
}