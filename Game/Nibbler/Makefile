NAME	= lib_arcade_nibbler.so

CC	= g++

RM	= rm -f

SRCS	= ./Nibbler.cpp \
		  ./entryPoint.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -fPIC -shared

all: $(NAME)

$(NAME): $(SRCS)
	 $(CC) -o ../$(NAME) $(CPPFLAGS) $(SRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
