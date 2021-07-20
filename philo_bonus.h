
#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct	s_all
{
	int			number_of_philo;
	long int	time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meal;
	long int	start_time;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*dead;
}				t_all;

typedef struct s_philo
{
	int 			num;
	long int		last_ate;
	int 			num_eat;
	int 			alive;
	t_all			*all;
}				t_philo;



int	check_args_valid(int argc, char **argv);


/*
 * 	libft utils
 */

int	ft_isdigit(int c);
int	ft_atoi(const char *str);


long int	time_calculate(void);
void 	custom_print(t_philo *ph, long int time, char *message, int type);
void	ft_error_exit(char *error);
void	ft_free_error(char *error, t_philo *philo);

/*
 *  bonus functions
 */

long int	get_time(void);
void		custom_sleep(long int time);
void		philo_life(t_philo *ph);

#endif //PHILO_PHILO_H
