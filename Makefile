NAME	=	philo_bonus

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -pthread

SRC		:=	main.c libft_functions.c utils.c philo_life.c

OBJ 	:=	${SRC:.c=.o}

HEADERS	=	philo_bonus.h

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
