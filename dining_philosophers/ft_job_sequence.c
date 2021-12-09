#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->fork[philo->L_fork]));
	pthread_mutex_lock(&(philo->data->fork[philo->R_fork]));
	if (!philo->data->whois_die)
		printf("%ld %d has taken a fork\n",
		philo->data->flow_time, philo->p_id + 1);
}

void	ft_eat(t_philo *philo)
{
	philo->last_eat = philo->data->flow_time;
	philo->data->last_eat_table[philo->p_id] = philo->last_eat;
	if (!philo->data->whois_die)
		printf("%ld %d is eating\n", philo->data->flow_time, philo->p_id + 1);
	philo->flow_time += philo->data->tte;
	while (philo->data->flow_time - philo->last_eat < philo->data->tte)
	{
		if (philo->data->whois_die)
		{
			ft_drop_fork(philo);
			return ;
		}
		usleep(philo->data->tte / 2);
	}
	philo->is_eat++;
	pthread_mutex_lock(&philo->data->mutex_eat_all);
	if (philo->data->must_eat > 0 && philo->is_eat == philo->data->must_eat)
	{
		philo->data->is_eat_all++;
		philo->is_eat_done = 1;
	}
	pthread_mutex_unlock(&philo->data->mutex_eat_all);
}

void	ft_drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->L_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->R_fork]);
}

void	ft_sleep(t_philo *philo)
{
	if (!philo->data->whois_die)
		printf("%ld %d is sleeping\n", philo->data->flow_time, philo->p_id + 1);
	philo->flow_time += philo->data->tts;
	usleep(philo->data->tts * 1000);
}

void	ft_think(t_philo *philo)
{
	if (!philo->data->whois_die)
		printf("%ld %d is thinking\n", philo->data->flow_time, philo->p_id + 1);
}
