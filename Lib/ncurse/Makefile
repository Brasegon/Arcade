NAME	= lib_arcade_ncurses.so

CC	= g++

RM	= rm -f

SRCS	= ./Ncurses.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -fPIC -shared

all: $(NAME)

$(NAME): $(SRCS)
	 $(CC) -o ../$(NAME) $(CPPFLAGS) $(SRCS) -lncurses

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
