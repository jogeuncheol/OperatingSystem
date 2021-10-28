#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
} t_data;

void	*t_function(void *data)
{
	int	id;
	int	i = 0;
	// 쓰레드는 레지스터, 스택만 개별공간을 할당 받고,
	// 코드, 데이터, 힙 영역은 프로세스 공유를 한다.

	id = *((int *)data);
	while (1)
	{
		printf("%d : %d\n", id, i);
		i++;
		sleep(1);
	}
}

int main()
{
	pthread_t thread1;
	pthread_t thread2;
	int thread_id;
	int status;
	int a = 1;
	int b = 2;

	// 쓰레드 생성, t_function 함수의 인자로 a를 넘김.
	thread_id = pthread_create(&thread1, NULL, t_function, (void *)&a);
	if (thread_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	thread_id = pthread_create(&thread2, NULL, t_function, (void *)&b);
	if (thread_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}
	// 쓰레드의 종료를 기다림. fork의 wait과 비슷함.
	pthread_join(thread1, (void **)&status);
	pthread_join(thread2, (void **)&status);

	return (0);
}
