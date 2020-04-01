NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/Core/Core.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/Core/pp
CPPFLAGS += -Wall -Wextra -g3

all: core graphicals games

core: $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -Wl,--no-as-needed -ldl

clean:
	$(RM) $(OBJS)
	make clean -C ./Lib/nCurses
	make clean -C ./Lib/SFML
	make clean -C ./Lib/libcaca
	make clean -C ./Game/Nibbler
	make clean -C ./Game/SolarFox

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Lib/nCurses
	make fclean -C ./Lib/SFML
	make fclean -C ./Lib/libcaca
	make fclean -C ./Game/Nibbler
	make fclean -C ./Game/SolarFox

re: fclean all

graphicals:
	make -C ./Lib/nCurses
	make -C ./Lib/SFML
	make -C ./Lib/libcaca

games:
	make -C ./Game/Nibbler
	make -C ./Game/SolarFox

.PHONY: all clean fclean re

#core