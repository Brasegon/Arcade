/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_
#include "../IGraphLib.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
class SFML : public IGraphLib{
    public:
        SFML();
        void setGameList(vector<string>);
        void setLibList(vector<string>);
        void init_menu();
        void init_game();
        int displayMenu();
        void displayMap(map_info_t map);
        playerEvent getKey();
        ~SFML();

    protected:
    private:
        sf::RenderWindow _window;
        // for menu
        std::vector<string> libList;
        std::vector<sf::Text> textLib;
        std::vector<sf::RectangleShape> _map;
        sf::Text PrintLib;
        sf::Text PrintGame;
        sf::Font font;
        int keyMenu;
        sf::Vertex line[2];
        int x, y;
};

#endif /* !SFML_HPP_ */
