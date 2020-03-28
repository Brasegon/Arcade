NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/Core/Core.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/Core/pp
CPPFLAGS += -Wall -Wextra

all: $(NAME) lib

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -Wl,--no-as-needed -ldl

clean:
	$(RM) $(OBJS)
	make clean -C ./Lib/ncurse

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Lib/ncurse

re: fclean all

lib:
	make -C ./Lib/ncurse

.PHONY: all clean fclean re

#core
#games
#graphicals