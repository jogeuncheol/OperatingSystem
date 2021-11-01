#include "philo.h"

void	ft_free(t_data *share_data, pthread_t *thread)
{
	int i;

	i = 0;
	while (i < share_data->nop)
	{
		pthread_mutex_destroy(&(share_data->fork[i]));
		i++;
	}
	free(share_data->fork);
	share_data->fork = NULL;
	free(share_data->philo);
	share_data->philo = NULL;
	free(share_data->last_eat_table);
	share_data->last_eat_table = NULL;
	free(share_data);
	share_data = NULL;
	free(thread);
	thread = NULL;
}
