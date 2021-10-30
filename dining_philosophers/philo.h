#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int		p_id;
	int		L_fork;
	int		R_fork;
	int		is_eatAll;
	int		flow_time;
	int		is_die;
	struct	s_data *data;
}	t_philo;

typedef struct s_data
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				must_eat;
	long			start_time;
	long			flow_time;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_data;

int		ft_init(int argc, char *argv[], t_data **share_data, t_philo **philo);
void	ft_init_philo(int i, t_data *share_data, t_philo *philo);
void	ft_take_fork(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_drop_fork(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	*ft_scheduler(void *data);
long	ft_get_time();

#endif
