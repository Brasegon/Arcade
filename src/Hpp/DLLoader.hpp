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

template <typename T>
class DLLoader {
    public:
        void *_void_etoile;
        std::string _path;
    DLLoader(std::string const &path) {
        _path = path;
        _void_etoile = dlopen(_path.c_str(), RTLD_NOW);
        if (_void_etoile == NULL) {
            std::string error = dlerror();
            throw Exception(error);
        }
    }

    ~DLLoader() {
        if (dlclose(_void_etoile) != 0)
            throw Exception("Could not close library.");
    }

    DLLoader(DLLoader const &copy) {
        _path = copy._path;
        _void_etoile = dlopen(_path.c_str(), RTLD_NOW);
        if (_void_etoile == NULL)
            throw Exception("Library could not be opened.");
    }

    DLLoader &operator=(DLLoader const &copy) {
        if (&copy != this) {
            _void_etoile = copy._void_etoile;
        }
        return *this;
    }

    T *getInstance(std::string entry_point, int width = 20, int height = 20) {
        T	*(*ptr)(int, int);
        ptr = reinterpret_cast<T *(*)(int, int)>(dlsym(_void_etoile, entry_point.c_str()));
        if (ptr == NULL)
            return (NULL);
        return ptr(width, height);
    }

    protected:
    private:
};

#endif /* !DLLOADER_HPP_ */
