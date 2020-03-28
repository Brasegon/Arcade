/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** entry_point
*/

#include <iostream>
#include "Ncurses.hpp"
#include "../IGraphLib.hpp"

__attribute__((constructor))
void enter()
{
}

__attribute__((destructor))
void out()
{
}


extern "C" IGraphLib *entryPoint(int w, int h)
{
	return new Ncurses;
}