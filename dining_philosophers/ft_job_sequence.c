#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	if (philo->p_id != share_data->nop)
	{
		pthread_mutex_lock(&(share_data->fork[philo->L_fork]));
//		printf("[%ld] %d : has taken a L_fork\n", share_data->flow_time, philo->p_id);
		pthread_mutex_lock(&(share_data->fork[philo->R_fork]));
		printf("%ld %d has taken a fork\n", share_data->flow_time, philo->p_id + 1);
	}
	else
	{
		pthread_mutex_lock(&(share_data->fork[philo->R_fork]));
//		printf("[%ld] %d : has taken a R_fork\n", share_data->flow_time, philo->p_id);
		pthread_mutex_lock(&(share_data->fork[philo->L_fork]));
		printf("%ld %d has taken a fork\n", share_data->flow_time, philo->p_id + 1);
	}
//	printf("[%d] %d : has taken a fork\n", philo->flow_time, philo->p_id);
}

void	ft_eat(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	philo->last_eat = share_data->flow_time;
	share_data->last_eat_table[philo->p_id] = philo->last_eat;
/*	if (share_data->flow_time - philo->last_eat > share_data->ttd)
	{
		printf("%ld %d is died\n", share_data->flow_time, philo->p_id);
		exit(0);
	}*/
	printf("%ld %d is eating\n", share_data->flow_time, philo->p_id + 1);
	philo->flow_time += share_data->tte;
	usleep(share_data->tte * 1000);
	share_data->last_eat_table[philo->p_id] += share_data->flow_time - share_data->tte;
	philo->is_eat++;
	if (share_data->must_eat > 0 && philo->is_eat == share_data->must_eat)
	{
		pthread_mutex_lock(&share_data->mutex_eat_all);
		share_data->is_eat_all++;
		pthread_mutex_unlock(&share_data->mutex_eat_all);
	}
//	philo->last_eat = share_data->flow_time;
}

void	ft_drop_fork(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
//	printf("[%ld] %d : drop fork\n", share_data->flow_time, philo->p_id);
	pthread_mutex_unlock(&share_data->fork[philo->R_fork]);
	pthread_mutex_unlock(&share_data->fork[philo->L_fork]);
}

void	ft_sleep(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	printf("%ld %d is sleeping\n", share_data->flow_time, philo->p_id + 1);
	philo->flow_time += share_data->tts;
	usleep(share_data->tts * 1000);
}

void	ft_think(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	printf("%ld %d is thinking\n", share_data->flow_time, philo->p_id + 1);
}
