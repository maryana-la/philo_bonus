#include "philo_bonus.h"

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
		current = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) * 1000;
		if (current - begin < (long int)(time))
		{
			usleep(250);
			continue ;
		}
		break ;
	}
}

void	ft_error_exit(char *error)
{
	printf("%s\n", error);
	exit (1);
}

//void	ft_free_error(char *error, t_philo *philo)
//{
//	if (philo->all->forks)
//		free(philo->all->forks);
//	if (philo->ph)
//		free(philo->ph);
//	if (philo)
//		free(philo);
//	printf("%s\n", error);
//	exit (1);
//}
//
//void	custom_print(t_philo *ph, long int time, char *message, int type)
//{
//	pthread_mutex_lock(&ph->all->flag_lock);
//	if (!ph->all->flag)
//	{
//		pthread_mutex_lock(&ph->all->print);
//		printf("%ld\tms\t%d\t%s", time, ph->num, message);
//		pthread_mutex_unlock(&ph->all->print);
//	}
//	pthread_mutex_unlock(&ph->all->flag_lock);
//	if (type == 2)
//	{
//		pthread_mutex_lock(&ph->all->print);
//		printf("%ld\tms\t%d\t%s", time, ph->num, message);
//		pthread_mutex_unlock(&ph->all->print);
//	}
//}


int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}


int	ft_atoi(const char *str)
{
	int					minus;
	unsigned long long	num;

	num = 0;
	minus = 1;
	while (*str == '\t' || *str == '\n' || *str == ' ' ||
		   *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -minus;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - 48);
		if (num > 9223372036854775807 && minus == 1)
			return (-1);
		else if (num > 9223372036854775807 && minus == -1)
			return (0);
		str++;
	}
	return (minus * (int)num);
}
