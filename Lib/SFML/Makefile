NAME	= lib_arcade_sfml.so

CC	= g++

RM	= rm -f

SRCS	= ./SFML.cpp \
		  ./entryPoint.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -fPIC -shared

all: $(NAME)

$(NAME): $(SRCS)
	 $(CC) -o ../$(NAME) $(CPPFLAGS) $(SRCS) -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
