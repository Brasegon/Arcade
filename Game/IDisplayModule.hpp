/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019 [WSL: Debian]
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>
#include <vector>
class IDisplayModule {
    virtual ~IDisplayModule() = default;
    virtual void init() = 0;
    virtual void stop() = 0;
    virtual void update() = 0;
    virtual const std::string &getName() const = 0;

    protected:
    private:
};

#endif /* !IDISPLAYMODULE_HPP_ */
