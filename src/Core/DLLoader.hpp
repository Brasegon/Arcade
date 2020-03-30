/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include <iostream>
#include "MyExeption.hpp"

template <typename T>
class DLLoader {
    public:
        DLLoader(std::string const &path) {
            _path = path;
            _void_etoile = dlopen(_path.c_str(), RTLD_NOW);
            if (_void_etoile == NULL) {
                std::string error = dlerror();
                throw MyExeption(error);
            }
        }

        DLLoader(DLLoader const &copy) {
            _path = copy._path;
            _void_etoile = dlopen(_path.c_str(), RTLD_NOW);
            if (_void_etoile == NULL)
                throw MyExeption("Error : Library can't be opened.");
        }

        ~DLLoader() {
            if (dlclose(_void_etoile) != 0)
                throw MyExeption("Error : Can't close library.");
        }

        T *getInstance(std::string entry_point, int width = 20, int height = 20) {
            T	*(*ptr)(int, int);
            ptr = reinterpret_cast<T *(*)(int, int)>(dlsym(_void_etoile, entry_point.c_str()));
            if (ptr == NULL)
                return (NULL);
            return ptr(width, height);
        }

        DLLoader &operator=(DLLoader const &copy) {
            if (&copy != this) {
                _void_etoile = copy._void_etoile;
            }
            return *this;
        }

        void *_void_etoile;
    protected:
        std::string _path;
    private:
};

#endif /* !DLLOADER_HPP_ */
