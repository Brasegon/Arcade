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
            T	*(*ptr)();
            _path = path;
            _void_etoile = dlopen(_path.c_str(), RTLD_NOW);
            if (_void_etoile == NULL) {
                throw MyExeption(dlerror());
            }
            ptr = reinterpret_cast<T *(*)()>(dlsym(_void_etoile, "entryPoint"));
            if (ptr == NULL)
                throw MyExeption("Error : could not create the instance");
            instance = ptr();
        }

        DLLoader(DLLoader const &copy) {
            _path = copy._path;
            _void_etoile = dlopen(_path.c_str(), RTLD_NOW);
            if (_void_etoile == NULL)
                throw MyExeption("Error : Library can't be opened.");
        }

        ~DLLoader() {
            delete instance;
            dlclose(_void_etoile);
        }

        T *getInstance() const
        {
            return instance;
        }

        DLLoader &operator=(DLLoader const &copy) {
            if (&copy != this) {
                _void_etoile = copy._void_etoile;
            }
            return *this;
        }

    private:
        void *_void_etoile;
        std::string _path;
        T *instance;
};

#endif /* !DLLOADER_HPP_ */
