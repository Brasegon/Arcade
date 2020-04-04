/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** entryPoint
*/

#include <iostream>
#include "../IGameLib.hpp"
#include "Nibbler.hpp"

extern "C" game_lib *entryPoint()
{
	return new Nibbler();
}