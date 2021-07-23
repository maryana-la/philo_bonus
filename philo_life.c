#include "philo_bonus.h"

void ft_print(long int time, int num, char *message)
{
	printf("%ld\t ms \t%d\t%s\n", time, num, message);
//	ft_putnbr_fd(time, 1);
//	ft_putstr_fd("\tms\t", 1);
//	ft_putnbr_fd(num, 1);
//	ft_putstr_fd("\t", 1);
//	ft_putstr_fd(message, 1);
//	ft_putstr_fd("\n", 1);
}

void	*life_check(void *p)
{
	t_philo		*ph;

	ph = (t_philo *)p;
	while (1)
	{
		if ((get_time() - ph->last_ate) > (ph->all->time_to_die))
		{
			ph->alive = 0;
			sem_wait(ph->all->print);
//			ft_print((get_time() - ph->all->start_time), ph->num, "died");
			printf("%ld\t ms \t%d\tdied\n", (long int)(get_time() - ph->all->start_time), ph->num);
			sem_post(ph->all->dead);
			return (NULL);
		}
		if (ph->all->num_of_meal != -1 && ph->num_eat >= ph->all->num_of_meal)
		{
			ph->alive = 0;
			sem_wait(ph->all->print);
			sem_post(ph->all->dead);
			return (NULL);
		}
		usleep(20);
	}
}


void philo_life(t_philo *ph)
{
	pthread_t death;

	pthread_create(&death, NULL, &life_check, (void *)ph);

	while (ph->alive == 1)
	{
		sem_wait(ph->all->forks);
		sem_wait(ph->all->forks);
		ph->last_ate = get_time();
		sem_wait(ph->all->print);
		ft_print((ph->last_ate - ph->all->start_time), ph->num, "has taken first fork");
//		printf("%ld\t%d\thas taken first fork\n", (ph->last_ate - ph->all->start_time), ph->num);
//		sem_post(ph->all->print);
//		sem_wait(ph->all->print);
		ft_print((ph->last_ate - ph->all->start_time), ph->num, "has taken second fork");
//		printf("%ld\t%d\thas taken second fork\n", (ph->last_ate - ph->all->start_time), ph->num);
//		sem_post(ph->all->print);
//		sem_wait(ph->all->print);
		ft_print((ph->last_ate - ph->all->start_time), ph->num, "is eating");
//		printf("%ld\t%d\tis eating\n", (get_time() - ph->all->start_time), ph->num);
		sem_post(ph->all->print);
//		ph->last_ate = get_time();
		custom_sleep(ph->all->time_to_eat);
		sem_post(ph->all->forks);
		sem_post(ph->all->forks);
		ph->num_eat++;
		sem_wait(ph->all->print);
		ft_print((get_time() - ph->all->start_time), ph->num, "is sleeping");
//		printf("%ld\t%d\tis sleeping\n", (get_time() - ph->all->start_time), ph->num);
		sem_post(ph->all->print);
		custom_sleep(ph->all->time_to_sleep);
		sem_wait(ph->all->print);
		ft_print((get_time() - ph->all->start_time), ph->num, "is thinking");
//		printf("%ld\t%d\tis thinking\n", (get_time() - ph->all->start_time), ph->num);
		sem_post(ph->all->print);
	}
	pthread_join(death, NULL);
	exit (0);
}
