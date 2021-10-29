#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define	nop 2
#define ttd 400
#define tts 100
#define tte 100

typedef struct s_philo
{
	int		p_id;
	int		L_fork;
	int		R_fork;
	struct	s_data *data;
}	t_philo;

typedef struct s_data
{
	int		num_of_philo;
	int		sleep_time;
	int		think_time;
	int		eat_time;
	int		death_time;
	pthread_mutex_t	*fork;
	t_philo	*philo;
}	t_data;

void	ft_take_fork(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
//	if (philo->p_id % 2 == 0)
	{
		pthread_mutex_lock(&(share_data->fork[philo->L_fork]));
		printf("%d : I take left fork | ^^ |\n", philo->p_id);
		pthread_mutex_lock(&(share_data->fork[philo->R_fork]));
		printf("%d : I take right fork | ^^ |\n", philo->p_id);
	}
/*	else
	{
		pthread_mutex_lock(&share_data->fork[philo->R_fork]);
		printf("I take right fork | ^^ |\n");
		pthread_mutex_lock(&share_data->fork[philo->L_fork]);
		printf("I take left fork | ^^ |\n");
	}*/
}

void	ft_eat(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	printf("%d : eating spaghetti | Y ^^ Y |\n", philo->p_id);
	sleep(10);
	printf("%d : Im done | _ .._ |\n", philo->p_id);
}

void	ft_drop_fork(t_philo *philo)
{
	t_data	*share_data;

	share_data = philo->data;
	printf("%d : philosopher | v ^^ |\n", philo->p_id);
//	if (philo->p_id % 2 == 0)
	{
		pthread_mutex_unlock(&(share_data->fork[philo->L_fork]));
		printf("%d : I drop left fork | ^^ |\n", philo->p_id);
		pthread_mutex_unlock(&(share_data->fork[philo->R_fork]));
		printf("%d : I drop right fork | ^^ |\n", philo->p_id);
	}
/*	else
	{
		pthread_mutex_unlock(&share_data->fork[philo->R_fork]);
		write(1, "I drop right fork | ^^ |\n", 25);
		pthread_mutex_unlock(&share_data->fork[philo->L_fork]);
		write(1, "I drop left fork | ^^ |\n", 24);
	}*/

}

void	ft_sleep(t_philo *philo)
{
	printf("%d : Im going to sleep 10sec bye | Zzz..|\n", philo->p_id);
	usleep(tts * 1000);
}

void	*ft_job(void *data)
{
	t_philo	*philo;
	t_data	*share_data;
	
	philo = (t_philo *)data;
	share_data = philo->data;
	
	printf("Im %d philosopher\n", philo->p_id);
	printf("My left fork : %d\n", philo->L_fork);
	printf("My rifht fork : %d\n", philo->R_fork);
	while (1)
	{
//		if (philo->p_id == 1)
//			sleep(1);
		ft_take_fork(philo);
		ft_eat(philo);
		ft_drop_fork(philo);
		ft_sleep(philo);
		sleep(5);
	}
}

int main(int argc, char *argv[])
{
	// 2명일때. 테스트
	pthread_t	*thread;
	int			th_id;
	int			status;
	t_data		*share_data;
	t_philo		*philo;

	thread = malloc(sizeof(pthread_t) * nop);
	if (thread == NULL)
	{
		perror("malloc error : ");
		exit(0);
	}
	// 초기화. 공유메모리 할당, 철학자 수 할당.
	share_data = malloc(sizeof(t_data));
	share_data->philo = malloc(sizeof(t_philo) * nop);
	philo = share_data->philo;
	philo[0].data = share_data;
	philo[1].data = share_data;
	share_data->num_of_philo = nop;

	// 초기화. 포크 할당, 포크에 뮤텍스.
	share_data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nop);
	pthread_mutex_init(&(share_data->fork[0]), NULL);
	pthread_mutex_init(&(share_data->fork[1]), NULL);

	// 쓰레드 생성.
	th_id = pthread_create(&thread[0], NULL, ft_job, (void *)&philo[0]);
	if (th_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	// 철학자 정보 초기화.
	share_data->philo[0].p_id = 0;
	share_data->philo[0].L_fork = share_data->philo[0].p_id;
	share_data->philo[0].R_fork = (share_data->philo[0].p_id + 1) % nop;

	th_id = pthread_create(&thread[1], NULL, ft_job, (void *)&philo[1]);
	if (th_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	share_data->philo[1].p_id = 1;
	share_data->philo[1].L_fork = share_data->philo[1].p_id;
	share_data->philo[1].R_fork = (share_data->philo[1].p_id + 1) % nop;


	// 쓰레드의 종료를 기다린다. fork 의 wait과 비슷함.
	pthread_join(thread[0], (void **)&status);
	pthread_join(thread[1], (void **)&status);
}
