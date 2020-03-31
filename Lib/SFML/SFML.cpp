/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** SFML
*/

#include "SFML.hpp"

SFML::SFML()
{
    keyMenu = 0;
}
void SFML::setGameList(vector<string> vect)
{

}
void SFML::setLibList(vector<string> vect)
{
    libList = vect;
}

const char *setLibName(std::string Name) {
    std::stringstream ss(Name.c_str());
    std::string token;
    while (std::getline(ss, token, '_')) {
        cout << token << endl;
        if (!token.find("sfml")) {
            return "SFML";
        } else if (!token.find("ncurse")) {
            return "nCurses";
        }
    }
    return Name.c_str();
}

void SFML::init_menu()
{
    int posY = 0;

    _window.create({1280, 720, 32}, "My window");
    if (!font.loadFromFile("./Lib/SFML/arial.ttf"))
        exit(84);
    PrintLib.setFont(font);
    PrintGame.setFont(font);
    PrintLib.setString("Librairie List");
    PrintLib.setPosition({50, 0});
    PrintGame.setPosition({50, 70});
    PrintGame.setString("Game List");
    line[0] = sf::Vertex(sf::Vector2f(300.f, 0.f));
    line[1] = sf::Vertex(sf::Vector2f(300.f, 800.f));
    for (int i = 0; i < libList.size(); i += 1) {
        sf::Text text;
        textLib.push_back(text);
        textLib[i].setFont(font);
        textLib[i].setPosition({400, posY});
        textLib[i].setString(setLibName(libList[i]));
        posY += 40;
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keyMenu -= 1;
                if (keyMenu <= 0) {
                    keyMenu = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keyMenu += 1;
                if (keyMenu >= 1) {
                    keyMenu = 1;
                }
            }
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                textLib.clear();
                _window.close();
            }
            
        }
        _window.clear();
        if (keyMenu == 0) {
            PrintLib.setFillColor(sf::Color::Green);
            PrintGame.setFillColor(sf::Color::White);
        } else if (keyMenu == 1) {
            PrintLib.setFillColor(sf::Color::White);
            PrintGame.setFillColor(sf::Color::Green);
        }
        _window.draw(PrintLib);
        _window.draw(PrintGame);
        _window.draw(line, 2, sf::Lines);
        if (keyMenu == 0) {
            for (int i = 0; i < textLib.size(); i += 1) {
                _window.draw(textLib[i]);
            }
        }
        _window.display();
    } else {
        return (-1);
    }

}
void SFML::displayMap(map_info_t map)
{

}
playerEvent SFML::getKey()
{

}
SFML::~SFML()
{
}
