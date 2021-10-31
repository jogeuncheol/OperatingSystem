#include "philo.h"

void	*ft_job(void *data)
{
	t_philo	*philo;
	t_data	*share_data;

	philo = (t_philo *)data;
	share_data = philo->data;
//	share_data->flow_time = 0;
/*	printf("%d : share_data->ttd : %d\n", philo->p_id, share_data->ttd);
	printf("%d : share_data->nop : %d\n", philo->p_id, share_data->nop);
	printf("%d : philo->L_fork : %d\n", philo->p_id, philo->L_fork);
	printf("%d : philo->R_fork : %d\n", philo->p_id, philo->R_fork);*/
	while (!share_data->whois_die)
	{
		ft_take_fork(philo);
		ft_eat(philo);
		ft_drop_fork(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_join_thread(pthread_t *thread, int nop)
{
	int	i;

	i = 0;
	while (i < nop + 1)
		pthread_join(thread[i++], NULL);
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

int	ft_create_thread(t_data *share_data, t_philo *philo)
{
	pthread_t	*thread;
	int			pth_id;
	int			i;
	
	thread = malloc(sizeof(pthread_t) * (share_data->nop + 1));
	if (thread == NULL)
	{
		printf("malloc error : ");
		return (1);
	}
	if (ft_create_scheduler(&thread[share_data->nop], share_data) != 0)
		return (1);
	i = -1;
	while (++i < share_data->nop)
	{
		ft_init_philo(i, share_data, &philo[i]);
		pth_id = pthread_create(&thread[i], NULL, ft_job, (void *)&philo[i]);
		if (pth_id < 0)
			return (1);
		usleep(100); // <--
	}
	ft_join_thread(thread, share_data->nop);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*share_data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Usage : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat_all]\n");
		return (1);
	}
	ft_init(argc, argv, &share_data, &philo);
	if (ft_create_thread(share_data, philo) == 1)
		;
//		ft_error();
//	ft_free_data();
	return (0);
}
