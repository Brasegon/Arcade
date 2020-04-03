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
            dlclose(_void_etoile);
        }
        T *getInstance() {
            T	*(*ptr)();
            ptr = reinterpret_cast<T *(*)()>(dlsym(_void_etoile, "entryPoint"));
            if (ptr == NULL)
                return (NULL);
            return ptr();
        }

        DLLoader &operator=(DLLoader const &copy) {
            if (&copy != this) {
                _void_etoile = copy._void_etoile;
            }
            return *this;
        }

    protected:
        void *_void_etoile;
        std::string _path;
    private:
};

#endif /* !DLLOADER_HPP_ */
