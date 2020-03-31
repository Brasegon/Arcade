NAME	= lib_arcade_starfox.so

CC	= g++

RM	= rm -f

SRCS	= ./SolarFox.cpp \
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
