/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** MyExeption
*/

#ifndef MYEXEPTION_HPP_
#define MYEXEPTION_HPP_

#include <exception>
#include <string>

class MyExeption : std::exception {
    public:
        std::string _s;
        MyExeption(std::string s) : _s(s) {}
        ~MyExeption() throw () {}
        const char *what() const throw() { return _s.c_str();} 

    protected:
    private:
};

#endif /* !MYEXEPTION_HPP_ */
