#include "philo.h"

void	ft_pthread_detach(pthread_t *thread, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_detach(thread[i]);
		i++;
	}
}

int	ft_create_error();
