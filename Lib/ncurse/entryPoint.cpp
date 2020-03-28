/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** entry_point
*/

#include <iostream>
#include "Ncurses.hpp"
#include "../IGraphLib.hpp"

IGraphLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Ncurses();
    while (1) {
        if (ret->displayMenu() != 0)
            break;
    }
}

__attribute__((destructor))
void out()
{
	delete ret;
}


extern "C" IGraphLib *entryPoint()
{
	return ret;
}