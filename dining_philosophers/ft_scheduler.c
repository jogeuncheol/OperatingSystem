#include "philo.h"

long	ft_get_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		perror("gettimeofday error : ");
		return (1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*ft_scheduler(void *data)
{
	t_data *share_data;

	share_data = (t_data *)data;
	while (1)
	{
		share_data->flow_time = ft_get_time() - share_data->start_time;
	}
}
