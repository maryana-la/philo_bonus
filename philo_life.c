#include "philo_bonus.h"

void philo_life(t_philo *ph, int i)
{
	while (1)
	{
		sem_wait(ph->all->forks);
		printf("%ld\t%d\thas taken first fork\n", (long int)(get_time() - ph->all->start_time), (i + 1));
		sem_wait(ph->all->forks);
		printf("%ld\t%d\thas taken second fork\n", (long int)(get_time() - ph->all->start_time), (i + 1));
		printf("%ld\t%d\tis eating\n", (long int)(get_time() - ph->all->start_time), (i + 1));
		ph->last_ate = get_time();
		custom_sleep(ph->all->time_to_eat);
		sem_post(ph->all->forks);
		sem_post(ph->all->forks);
		ph->num_eat++;

		printf("%ld\t%d\tis sleeping\n", (long int)(get_time() - ph->all->start_time), i + 1);
		custom_sleep(ph->all->time_to_sleep);
		printf("%ld\t%d\tis thinking\n", (long int)(get_time() - ph->all->start_time), i + 1);
	}
}
