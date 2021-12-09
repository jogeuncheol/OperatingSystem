#include "philo.h"

int	ft_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\t'
			|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	if (result > 9223372036854775807)
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return (result * sign);
}
