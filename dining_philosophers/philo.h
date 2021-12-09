#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				p_id;
	int				L_fork;
	int				R_fork;
	long			is_eat;
	int				is_eat_done;
	long			flow_time;
	long			is_die;
	long			last_eat;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long			nop;
	long			ttd;
	long			tte;
	long			tts;
	long			must_eat;
	long			whois_die;
	long			start_time;
	long			flow_time;
	long			*last_eat_table;
	long			is_eat_all;
	pthread_mutex_t	mutex_eat_all;
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
long	ft_get_time(void);
void	ft_wsleep(int time_to);
void	ft_pthread_detach(pthread_t *thread, int n);
int		ft_free(t_data *share_data, pthread_t *thread);
int		ft_error(t_data *share_data, int errno);
int		ft_arguments_validation(int argc, char *argv[]);
int		ft_sign_validation(t_data *share_data);
int		ft_integer_validation(t_data *share_data);
long	ft_atoi(const char *str);

#endif
