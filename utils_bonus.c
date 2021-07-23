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
	while (*str == '\t' || *str == '\n' || *str == ' ' || \
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	char	a;

	if (n == -2147483648)
	{
		write(1, "-2", 2);
		ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n >= 0 && n <= 9)
	{
		a = n + '0';
		ft_putchar(a);
	}
}

void	ft_putstr(char *s)
{
	int		i;
	char	string;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			string = s[i];
			write(1, &string, 1);
			i++;
		}
	}
}
