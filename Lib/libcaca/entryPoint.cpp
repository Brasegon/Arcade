/*
** EPITECH PROJECT, 2020
** Arcade [WSL: Debian]
** File description:
** entry_point
*/

#include <iostream>
#include "libcaca.hpp"
#include "../IGraphLib.hpp"

extern "C" IGraphLib *entryPoint()
{
	return new CACA();
}