/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML()
{
}
void SFML::setGameList(vector<string> vect)
{

}
void SFML::setLibList(vector<string> vect)
{
    libList = vect;
}
void SFML::init_menu()
{
    _window.create({800, 800, 32}, "My window");
    for (int i = 0; i < libList.size(); i += 1) {
    }
}
void SFML::init_game()
{

}
int SFML::displayMenu()
{
    if (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.display();
    } else {
        return (-1);
    }

}
void SFML::displayMap(map_info_t map)
{

}
int SFML::getKey()
{

}
SFML::~SFML()
{
}
