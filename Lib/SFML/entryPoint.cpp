/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** entryPoint
*/

#include <iostream>
#include "SFML.hpp"

extern "C" IGraphLib *entryPoint()
{
	return new SFML();
}