/*
** EPITECH PROJECT, 2020
** Arcade
** File description:
** IGraphical_lib
*/

#ifndef IGraphical_lib_HPP_
#define IGraphical_lib_HPP_

class IGraphical_lib {
    public:
        virtual ~IGraphical_lib() = 0;

        virtual int menu() = 0;
        virtual void clear() = 0;
        virtual int getKey() = 0;

    protected:
    private:
};

#endif /* !IGraphical_lib_HPP_ */
