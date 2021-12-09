#include "philo.h"

void	*ft_job(void *data)
{
	t_philo	*philo;
	t_data	*share_data;

	philo = (t_philo *)data;
	share_data = philo->data;
	while (!share_data->whois_die && share_data->is_eat_all != share_data->nop)
	{
		if (philo->is_eat_done == 1)
			break ;
		ft_take_fork(philo);
		ft_eat(philo);
		ft_drop_fork(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

int	ft_join_thread(pthread_t *thread, int nop)
{
	int	i;

	i = 0;
	while (i < nop + 1)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			ft_pthread_detach(thread, i + 1);
			return (16);
		}
		i++;
	}
	return (0);
}

int	ft_create_scheduler(pthread_t *thread, t_data *share_data)
{
	int	pth_id;

	pth_id = pthread_create(thread, NULL, ft_scheduler, (void *)share_data);
	if (pth_id < 0)
		return (1);
	share_data->start_time = ft_get_time();
	return (0);
}

int	ft_create_thread(t_data *share_data, t_philo *philo, pthread_t **pth)
{
	pthread_t	*thread;
	int			pth_id;
	long		i;

	thread = malloc(sizeof(pthread_t) * (share_data->nop + 1));
	if (thread == NULL)
		return (15);
	if (ft_create_scheduler(&thread[share_data->nop], share_data) != 0)
		return (16);
	i = -1;
	while (++i < share_data->nop)
		ft_init_philo(i, share_data, &philo[i]);
	i = -1;
	while (++i < share_data->nop)
	{
		pth_id = pthread_create(&thread[i], NULL, ft_job, (void *)&philo[i]);
		if (pth_id < 0)
			return (30);
	}
	*pth = thread;
	if (ft_join_thread(thread, share_data->nop))
		return (17);
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t	*thread;
	t_data		*share_data;
	t_philo		*philo;
	int			ret;

	if (argc < 5 || argc > 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die"
		"time_to_eat time_to_sleep [must_eat_all]\n");
		return (1);
	}
	if (ft_arguments_validation(argc, argv) == 1)
	{
		printf("Wrong arguments : Check arguments\n");
		return (1);
	}
	ret = ft_init(argc, argv, &share_data, &philo);
	if (ret != 0)
		return (ft_error(share_data, ret));
	ret = ft_create_thread(share_data, philo, &thread);
	if (ret != 0)
		return (ft_error(share_data, ret));
	return (ft_free(share_data, thread));
}
