#include "philo_bonus.h"

void	ft_print(long int time, int num, char *message)
{
	ft_putnbr(time);
	ft_putstr("\tms\t");
	ft_putnbr(num);
	ft_putstr("\t");
	ft_putstr(message);
	ft_putstr("\n");
}

void	*life_check(void *p)
{
	t_philo		*ph;

	ph = (t_philo *)p;
	while (1)
	{
		if ((get_time() - ph->last_ate) > (ph->all->time_to_die))
		{
			sem_wait(ph->all->flag_death);
			ph->alive = 0;
			sem_post(ph->all->flag_death);
			sem_wait(ph->all->print);
			ft_print((get_time() - ph->all->start_time), ph->num, "died");
			exit (2);
		}
		usleep(200);
	}
}

int	eating(t_philo *ph)
{
	sem_wait(ph->all->forks);
	sem_wait(ph->all->forks);
	sem_wait(ph->all->flag_death);
	if (ph->alive != 1)
		return (1);
	ph->last_ate = get_time();
	sem_post(ph->all->flag_death);
	sem_wait(ph->all->print);
	ft_print((get_time() - ph->all->start_time), ph->num, \
		"has taken forks");
	sem_post(ph->all->print);
	sem_wait(ph->all->print);
	ft_print((get_time() - ph->all->start_time), ph->num, "is eating");
	sem_post(ph->all->print);
	custom_sleep(ph->all->time_to_eat);
	sem_post(ph->all->forks);
	sem_post(ph->all->forks);
	if (ph->all->num_of_meal > 0 && ++ph->num_eat >= ph->all->num_of_meal)
		exit (1);
	return (0);
}

int	philo_life(t_philo *ph)
{
	pthread_t	death;

	if (!(ph->num % 2))
		custom_sleep(ph->all->time_to_eat);
	pthread_create(&death, NULL, &life_check, (void *)ph);
	while (ph->alive == 1)
	{
		if (eating(ph) == 1)
			break ;
		sem_wait(ph->all->print);
		ft_print((get_time() - ph->all->start_time), ph->num, "is sleeping");
		sem_post(ph->all->print);
		custom_sleep(ph->all->time_to_sleep);
		sem_wait(ph->all->print);
		ft_print((get_time() - ph->all->start_time), ph->num, "is thinking");
		sem_post(ph->all->print);
	}
	pthread_join(death, NULL);
	exit (2);
}
