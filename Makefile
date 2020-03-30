NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/Core/Core.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/Core/pp
CPPFLAGS += -Wall -Wextra -g3

all: $(NAME) graphicals

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -Wl,--no-as-needed -ldl

clean:
	$(RM) $(OBJS)
	make clean -C ./Lib/nCurses
	make clean -C ./Lib/SFML

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Lib/nCurses
	make fclean -C ./Lib/SFML

re: fclean all

graphicals:
	make -C ./Lib/nCurses
	make -C ./Lib/SFML

games:
	make -C ./Game/Nibbler

.PHONY: all clean fclean re

#core