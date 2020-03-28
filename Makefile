NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/Core/Core.cpp 

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./src/Core/pp
CPPFLAGS += -Wall -Wextra

all: $(NAME) graphicals

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -Wl,--no-as-needed -ldl

clean:
	$(RM) $(OBJS)
	make clean -C ./Lib/nCurses

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Lib/nCurses

re: fclean all

graphicals:
	make -C ./Lib/nCurses

.PHONY: all clean fclean re

#core
#games