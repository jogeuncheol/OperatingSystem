#include "philo.h"

void	ft_init_philo(int i, t_data *share_data, t_philo *philo)
{
	philo->p_id = i;
	philo->L_fork = i;
	philo->R_fork = (i + 1) % share_data->nop;
	if (share_data->must_eat > 0)
		philo->is_eat_done = 0;
	else
		philo->is_eat_done = -1;
	philo->is_eat = 0;
	philo->is_die = 0;
	philo->flow_time = 0;
	philo->last_eat = 0;
	philo->data = share_data;
}

int	ft_init_mutex(t_data *share_data)
{
	long	i;

	i = 0;
	while (i < share_data->nop)
	{
		if (pthread_mutex_init(&(share_data->fork[i]), NULL) != 0)
			return (21 + i);
		i++;
	}
	if (pthread_mutex_init(&share_data->mutex_eat_all, NULL) != 0)
		return (20);
	return (0);
}

int	ft_init_eating_table(t_data *share_data)
{
	long	i;

	share_data->last_eat_table = malloc(sizeof(long) * share_data->nop);
	if (share_data->last_eat_table == NULL)
		return (1);
	i = 0;
	while (i < share_data->nop)
	{
		share_data->last_eat_table[i] = 0;
		i++;
	}
	return (0);
}

void	ft_init_share_data(int argc, char *argv[], t_data *share_data)
{
	share_data->nop = ft_atoi(argv[1]);
	share_data->ttd = ft_atoi(argv[2]);
	share_data->tte = ft_atoi(argv[3]);
	share_data->tts = ft_atoi(argv[4]);
	if (argc == 6)
		share_data->must_eat = ft_atoi(argv[5]);
	else
		share_data->must_eat = -1;
	share_data->whois_die = 0;
	share_data->is_eat_all = 0;
	share_data->start_time = ft_get_time();
	share_data->philo = NULL;
	share_data->fork = NULL;
	share_data->last_eat_table = NULL;
}

// nop, ttd, tte, tts, must_eat 초기화.
int	ft_init(int argc, char *argv[], t_data **share_data, t_philo **philo)
{
	*share_data = malloc(sizeof(t_data));
	if (share_data == NULL)
		return (11);
	ft_init_share_data(argc, argv, *share_data);
	if (ft_sign_validation(*share_data) == 1)
		return (-10);
	if (ft_integer_validation(*share_data) == 1)
		return (-11);
	(*share_data)->philo = malloc(sizeof(t_philo) * (*share_data)->nop);
	if ((*share_data)->philo == NULL)
		return (12);
	*philo = (*share_data)->philo;
	(*share_data)->fork = malloc(sizeof(pthread_mutex_t) * (*share_data)->nop);
	if ((*share_data)->fork == NULL)
		return (13);
	if (ft_init_eating_table(*share_data) == 1)
		return (14);
	return (ft_init_mutex(*share_data));
}
