all:
	gcc -g main_bonus.c utils_bonus.c philo_life.c -lpthread -ophilo

clean:
	rm philo