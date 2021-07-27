/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:53:13 by rchelsea          #+#    #+#             */
/*   Updated: 2021/07/27 15:53:14 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

typedef struct s_all
{
	int			num_of_philo;
	long int	time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_meal;
	long int	start_time;
	sem_t		*forks;
	sem_t		*print;
	sem_t		*dead;
	sem_t		*flag_death;
}				t_all;

typedef struct s_philo
{
	int		num;
	long	last_ate;
	int		num_eat;
	int		alive;
	t_all	*all;
}				t_philo;

/*
 * 	main
 */

t_philo		philo_init(t_all *all);
void		monitor_process_exit(t_philo *ph, pid_t *pid);
void		launch_processes(t_philo *ph, pid_t *pid);
void		close_free(t_philo *ph, pid_t *pid);

/*
 * 	philo_life
 */
int			philo_life(t_philo *ph);
void		*life_check(void *p);
int			eating(t_philo *ph);

/*
 * 	utils
 */
int			check_args_valid(int argc, char **argv);
void		init_structure(t_all *all, int argc, char **argv);
void		ft_print(long int time, int num, char *message);
long int	get_time(void);
void		custom_sleep(long int time);

/*
 * 	libft utils
 */
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_putchar(char c);
void		ft_putnbr(int n);
void		ft_putstr(char *s);

#endif
