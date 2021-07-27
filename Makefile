# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 15:53:09 by rchelsea          #+#    #+#              #
#    Updated: 2021/07/27 15:53:10 by rchelsea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -pthread

SRC		:=	main.c libft_functions.c utils.c philo_life.c

O_FOLD	=	objs/

OBJ 	:=	$(addprefix $(O_FOLD), ${SRC:.c=.o})

HEADERS	=	philo_bonus.h

$(O_FOLD)%.o : %.c $(HEADERS)
	@mkdir -p $(O_FOLD)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	@rm -rf $(O_FOLD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
