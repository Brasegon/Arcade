/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGame_lib
*/

#ifndef IGAME_LIB_HPP_
#define IGAME_LIB_HPP_

class IGame_lib {
    public:
        virtual ~IGame_lib() = 0;
        /*map_info_t*/ virtual std::vector<std::string> getMap() = 0;

    protected:
    private:
};

#endif /* !IGAME_LIB_HPP_ */
