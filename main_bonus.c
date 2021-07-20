#include "philo_bonus.h"

int	check_args_valid(int argc, char **argv)
{
	int i;
	int j;

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
	all->number_of_philo = ft_atoi(argv[1]);
	all->time_to_die = (long int) ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]) * 1000;
	all->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		all->num_of_meal = ft_atoi(argv[5]);
	else
		all->num_of_meal = -1;
	if (all->number_of_philo < 1 || all->time_to_die < 1 || all->time_to_eat < 1 || all->time_to_sleep < 1 || all->num_of_meal == 0)
	{
		write(1, "Argument is too small\n", 22);
		exit (1);
	}
}

t_philo	philo_init(t_all *all)
{
	t_philo	philo;
//	int		i;
//
//	i = -1;
//	philo = malloc(sizeof(t_philo) * (all->number_of_philo + 1));
//	if (!philo)
//		return (NULL);
//	while (++i < all->number_of_philo)
//	{
//		philo[i].num = i + 1;
//		philo[i].last_ate = 0;
//		philo[i].num_eat = 0;
//		philo[i].all = all;
//	}
	philo.last_ate = 0;
	philo.num_eat = 0;
	philo.alive = 1;
	philo.all = all;
	return (philo);
}

int main (int argc, char **argv)
{
	t_all all;
	t_philo ph;
	pid_t 	*pid;

	check_args_valid(argc, argv);
	init_structure(&all, argc, argv);
	ph = philo_init(&all);

	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("dead");
	ph.all->forks = sem_open("fork", O_CREAT, 0666, ph.all->number_of_philo);
	if (ph.all->forks == SEM_FAILED)
	{
		write(1, "Sem failed_fork\n", 11);
		return (1);
	}
	ph.all->print = sem_open("print", O_CREAT, 0666, 1);
	if (ph.all->forks == SEM_FAILED)
	{
		write(1, "Sem failed_print\n", 17);
		return (1);
	}
	ph.all->dead = sem_open("dead", O_CREAT, 0666, 1);
	if (ph.all->dead == SEM_FAILED)
	{
		write(1, "Sem failed_dead\n", 11);
		return (1);
	}



	pid = (pid_t *)(malloc(sizeof(pid_t) * ph.all->number_of_philo));

	int i;
	i = -1;
	sem_wait(ph.all->dead);
//	ph.all->start_time = get_time();
	while (++i < all.number_of_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			write(1, "Failed to create fork\n", 22);
			exit (1);
		}
		if (pid[i] == 0)
		{
//			if (i % 2)
//				usleep (50);
			ph.all->start_time = get_time();
			ph.num = i + 1;
			ph.last_ate = get_time();
			philo_life(&ph);
		}
	}
	sem_wait(ph.all->dead);
	i = -1;
	while (++i < all.number_of_philo)
		kill(pid[i], SIGKILL);
	wait(NULL);

	sem_close(ph.all->forks);
	sem_close(ph.all->print);
	sem_close(ph.all->dead);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("dead");
	if (pid)
		free(pid);
	return (0);
}

