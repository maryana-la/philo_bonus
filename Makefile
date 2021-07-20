all:
	gcc -g main_bonus.c utils_bonus.c philo_life.c libft/libft.a -lpthread -ophilo_bonus

clean:
	rm philo_bonus