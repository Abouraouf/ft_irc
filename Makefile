NAME =  irc
SOURCES = main.cpp srcs/Server.cpp
FLAGS = -Wall -Wextra -Werror -std=c++98
OBJ = $(SOURCES:.cpp=.o)
HEADER = headers/Server.hpp headers/Client.hpp 
%.o: %.cpp $(HEADER)
	c++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) 
	c++ $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all