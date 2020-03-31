/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** entryPoint
*/

#include <iostream>
#include "../IGameLib.hpp"
#include "SolarFox.hpp"

game_lib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new SolarFox();
}

__attribute__((destructor))
void out()
{
	delete ret;
}


extern "C" game_lib *entryPoint()
{
	return ret;
}