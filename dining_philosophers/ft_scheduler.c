#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		perror("gettimeofday error : ");
		return (1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_wsleep(int time_to)
{
	int		i;

	i = 0;
	while (i < time_to)
	{
		usleep(1000);
		i++;
	}
}

int	ft_died_check(t_data *share_data)
{
	long	i;

	i = 0;
	while (i < share_data->nop)
	{
		if (share_data->flow_time
			- share_data->last_eat_table[i] > share_data->ttd)
		{
			printf("%ld %ld is died\n", share_data->flow_time, i + 1);
			share_data->whois_die = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*ft_scheduler(void *data)
{
	t_data	*share_data;

	share_data = (t_data *)data;
	share_data->start_time = ft_get_time();
	while (1)
	{
		if (share_data->whois_die || share_data->is_eat_all == share_data->nop)
			break ;
		share_data->flow_time = ft_get_time() - share_data->start_time;
		if (ft_died_check(share_data))
			break ;
	}
	return (NULL);
}
