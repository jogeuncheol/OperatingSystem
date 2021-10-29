#include "philo.h"

void	ft_take_fork(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	pthread_mutex_lock(&(share_data->fork[philo->L_fork]));
	pthread_mutex_lock(&(share_data->fork[philo->R_fork]));
	printf("%d : has taken a fork\n", philo->p_id);
}

void	ft_eat(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	printf("%d : is eating\n", philo->p_id);
	philo->flow_time += share_data->tte;
	usleep(share_data->tte * 1000);
}

void	ft_drop_fork(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	printf("%d : drop fork\n", philo->p_id);
	pthread_mutex_unlock(&share_data->fork[philo->R_fork]);
	pthread_mutex_unlock(&share_data->fork[philo->L_fork]);
}

void	ft_sleep(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	philo->flow_time += share_data->tts;
	printf("%d : is sleeping\n", philo->p_id);
	usleep(share_data->tts * 1000);
}
