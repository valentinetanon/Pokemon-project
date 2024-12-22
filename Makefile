##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME = pokemon

SRCS = main.cpp \
       attack.cpp \
       pokemon.cpp \
       core.cpp

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = -I./include -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(CPPFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 
	rm -f pokemons.txt

re: fclean all

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@
