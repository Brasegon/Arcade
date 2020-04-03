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
    x = 200;
    y = 50;
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
    _window.create({1280, 720, 32}, "My window");
}
playerEvent SFML::displayMenu()
{
    
    if (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (keyMenu == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                _window.close();
                return (PE_RESTART);
            }
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
        return (PE_EXIT);
    }
    return (PE_NOACTION);
}
void SFML::displayMap(map_info_t map)
{
    if (_window.isOpen()) {
        sf::Event event;
        for (int i = 0; i < map.map.size(); i += 1) {
            for (int j = 0; j < map.map[i].size(); j += 1) {
                sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
                switch (map.map[i][j])
                {
                case 'X':
                case 'T':
                    rectangle.setPosition(x, y);
                    _map.push_back(rectangle);
                    break;
                case '>':
                case '^':
                case '<':
                case 'v':
                    rectangle.setFillColor(sf::Color::Green);
                    rectangle.setPosition(x, y);
                    _map.push_back(rectangle);
                    break;
                case 'O':
                case 'o':
                    rectangle.setFillColor(sf::Color::Blue);
                    rectangle.setPosition(x, y);
                    _map.push_back(rectangle);
                    break;
                case 'P':
                    rectangle.setFillColor(sf::Color::Yellow);
                    rectangle.setPosition(x, y);
                    _map.push_back(rectangle);
                    break;
                case 'E':
                    rectangle.setFillColor(sf::Color::Magenta);
                    rectangle.setPosition(x, y);
                    _map.push_back(rectangle);
                    break;
                case '6':
                case '3':
                case '4':
                case 'Y':
                    rectangle.setFillColor(sf::Color::Red);
                    rectangle.setPosition(x, y);
                    _map.push_back(rectangle);
                    break;
                }
                x += 20;
            }
            x = 200;
            y += 20;
        }
        x = 200;
        y = 50;
        while (_window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                textLib.clear();
                _window.close();
            }
            
        }
        _window.clear();
        for (int i = 0; i < _map.size(); i += 1) {
            _window.draw(_map[i]);
        }
        _map.clear();
        _window.display();
    } else {
        return ;
    }
}
playerEvent SFML::getKey()
{

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            return PE_UP;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            return PE_DOWN;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            return PE_LEFT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            return PE_RIGHT;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            return PE_ACTION1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            return PE_ACTION2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            return PE_ACTION3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            _window.close();
            return PE_NEXT_LIB;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            _window.close();
            return PE_PREV_LIB;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            _window.close();
            return PE_NEXT_GAME;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            _window.close();
            return PE_PREV_GAME;
        }
        return PE_NOACTION;
}
SFML::~SFML()
{
}
