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
class SFML : public IGraphLib{
    public:
        SFML();
        void setGameList(vector<string>);
        void setLibList(vector<string>);
        void init_menu();
        void init_game();
        int displayMenu();
        void displayMap(map_info_t map);
        int getKey();
        ~SFML();

    protected:
    private:
        sf::RenderWindow _window;
        std::vector<string> libList;
        std::vector<sf::String> textLib;
};

#endif /* !SFML_HPP_ */
