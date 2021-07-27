/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:53:04 by rchelsea          #+#    #+#             */
/*   Updated: 2021/07/27 15:53:04 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_all	all;
	t_philo	ph;
	pid_t	*pid;

	check_args_valid(argc, argv);
	init_structure(&all, argc, argv);
	ph = philo_init(&all);
	pid = (pid_t *)(malloc(sizeof(pid_t) * ph.all->num_of_philo));
	launch_processes(&ph, pid);
	close_free(&ph, pid);
	return (0);
}

t_philo	philo_init(t_all *all)
{
	t_philo	philo;

	philo.num_eat = 0;
	philo.alive = 1;
	philo.all = all;
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("flag_death");
	philo.all->forks = sem_open("fork", O_CREAT, 0666, philo.all->num_of_philo);
	philo.all->print = sem_open("print", O_CREAT, 0666, 1);
	philo.all->dead = sem_open("dead", O_CREAT, 0666, 1);
	philo.all->flag_death = sem_open("flag_death", O_CREAT, 0666, 1);
	if (philo.all->forks == SEM_FAILED || philo.all->print == SEM_FAILED || \
		philo.all->dead == SEM_FAILED || philo.all->flag_death == SEM_FAILED)
	{
		write(1, "Sem failed\n", 11);
		exit (1);
	}
	return (philo);
}

void	monitor_process_exit(t_philo *ph, pid_t *pid)
{
	int	full;
	int	status;
	int	j;
	int	i;

	full = 0;
	i = -1;
	while (++i < ph->all->num_of_philo)
	{
		j = -1;
		status = 0;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 2)
			{
				while (++j < ph->all->num_of_philo)
					kill(pid[j], SIGKILL);
				break ;
			}
			else if (WEXITSTATUS(status) == 1)
				if (++full == ph->all->num_of_philo)
					break ;
		}
	}
}

void	launch_processes(t_philo *ph, pid_t *pid)
{
	int	i;

	i = -1;
	ph->all->start_time = get_time();
	while (++i < ph->all->num_of_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			write(1, "Failed to create fork\n", 22);
			exit (1);
		}
		if (pid[i] == 0)
		{
			ph->num = i + 1;
			ph->last_ate = get_time();
			philo_life(ph);
		}
	}
	monitor_process_exit(ph, pid);
}

void	close_free(t_philo *ph, pid_t *pid)
{
	sem_close(ph->all->forks);
	sem_close(ph->all->print);
	sem_close(ph->all->dead);
	sem_close(ph->all->flag_death);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("flag_death");
	if (pid)
		free(pid);
}
