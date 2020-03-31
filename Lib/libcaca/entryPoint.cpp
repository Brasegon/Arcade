/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** entry_point
*/

#include <iostream>
#include "libcaca.hpp"
#include "../IGraphLib.hpp"

IGraphLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new CACA();
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