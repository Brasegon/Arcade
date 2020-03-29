/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** entryPoint
*/

#include <iostream>
#include "SFML.hpp"

IGraphLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new SFML();
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