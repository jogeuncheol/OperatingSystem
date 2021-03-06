#include "philo.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_arguments_validation(int argc, char *argv[])
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_is_digit(argv[i][j]))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_sign_validation(t_data *share_data)
{
	if (share_data->nop <= 0)
		return (1);
	else if (share_data->ttd <= 0)
		return (1);
	else if (share_data->tte <= 0)
		return (1);
	else if (share_data->tts <= 0)
		return (1);
	else if ((long long)share_data->must_eat < -1)
		return (1);
	return (0);
}

int	ft_integer_validation(t_data *share_data)
{
	if (share_data->nop > 4294967295)
		return (1);
	else if (share_data->ttd > 4294967295)
		return (1);
	else if (share_data->tte > 4294967295)
		return (1);
	else if (share_data->tts > 4294967295)
		return (1);
	else if (share_data->must_eat > 4294967295)
		return (1);
	return (0);
}
