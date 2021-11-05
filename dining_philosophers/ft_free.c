#include "philo.h"

void	ft_err_message(int errno)
{
	if (errno == 11)
		printf("malloc error : t_data *share_data\n");
	else if (errno == 12)
		printf("malloc error : t_philo *philo\n");
	else if (errno == 13)
		printf("malloc error : pthread_mutex_t *fork\n");
	else if (errno == 14)
		printf("malloc error : long *last_eat_table\n");
	else if (errno == 20)
		printf("pthread_mutex_init error : mutex_eat_all\n");
	else
		printf("pthread_mutex_init error : [mutex] fork\n");
}

void	ft_free_share_data(t_data *share_data)
{
	if (share_data != NULL)
	{
		if (share_data->philo != NULL)
		{
			free(share_data->philo);
			share_data->philo = NULL;
		}
		if (share_data->fork != NULL)
		{
			free(share_data->fork);
			share_data->fork = NULL;
		}
		if (share_data->last_eat_table != NULL)
		{
			free(share_data->last_eat_table);
			share_data->last_eat_table = NULL;
		}
		free(share_data);
		share_data = NULL;
	}
}

void	ft_mutex_destroy(t_data *share_data, int errno)
{
	int i;

	i = 0;
	while (i < errno - 21)
	{
		pthread_mutex_destroy(&(share_data->fork[i]));
		i++;
	}
}

int	ft_error(t_data	*share_data, int errno)
{
	if (errno > 20)
		ft_mutex_destroy(share_data, errno);
	else if (errno == 20)
		ft_mutex_desrtoy(share_data, share_data->nop);
	ft_free_share_data(share_data);
	ft_err_message(errno);
	return (errno);
}

void	ft_free(t_data *share_data, pthread_t *thread)
{
	int i;

	i = 0;
	while (i < share_data->nop)
	{
		pthread_mutex_destroy(&(share_data->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&share_data->mutex_eat_all);
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
