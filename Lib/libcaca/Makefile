NAME	= lib_arcade_libcaca.so

CC	= g++

RM	= rm -f

SRCS	= ./libcaca.cpp \
		  ./entryPoint.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -fPIC -shared -L./lib -lcaca

all: $(NAME)

$(NAME): $(SRCS)
	 $(CC) -o ../$(NAME) $(CPPFLAGS) $(SRCS) -lncurses

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
