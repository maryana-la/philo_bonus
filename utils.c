/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:53:22 by rchelsea          #+#    #+#             */
/*   Updated: 2021/07/27 15:53:23 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args_valid(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		write(1, "Wrong number of arguments\n", 27);
		exit (1);
	}
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(1, "Invalid argument\n", 17);
				exit (1);
			}
		}
	}
	return (0);
}

void	init_structure(t_all *all, int argc, char **argv)
{
	all->num_of_philo = ft_atoi(argv[1]);
	all->time_to_die = (long int) ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]) * 1000;
	all->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		all->num_of_meal = ft_atoi(argv[5]);
	else
		all->num_of_meal = -1;
	if (all->num_of_philo < 1 || all->time_to_die < 1 || \
		all->time_to_eat < 1 || all->time_to_sleep < 1 || all->num_of_meal == 0)
	{
		write(1, "Argument is too small\n", 22);
		exit (1);
	}
}

void	ft_print(long int time, int num, char *message)
{
	ft_putnbr(time);
	ft_putstr("\tms\t");
	ft_putnbr(num);
	ft_putstr("\t");
	ft_putstr(message);
	ft_putstr("\n");
}

long int	get_time(void)
{
	long int		current;
	struct timeval	now;

	gettimeofday(&now, NULL);
	current = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (current);
}

void	custom_sleep(long int time)
{
	long int		begin;
	long int		current;
	struct timeval	begin_time;
	struct timeval	current_time;

	gettimeofday(&begin_time, NULL);
	begin = (begin_time.tv_sec * 1000 + begin_time.tv_usec / 1000) * 1000;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		current = (current_time.tv_sec * 1000 + \
			current_time.tv_usec / 1000) * 1000;
		if (current - begin < (long int)(time))
		{
			usleep(500);
			continue ;
		}
		break ;
	}
}
