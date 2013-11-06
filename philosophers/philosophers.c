#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "philosophers.h"

/*
Notes :
- Necessite de changer le code pour l'adapter à l'os
- Utiliser le try_lock de l'os pour eviter les interblocages (superiorite de l'os sur Linux)
*/

void philosophers_process(void)
{
	int i;
	pthread_t philosophers_id[PHILOSOPHERS_NUMBER];
	int philosophers_data[PHILOSOPHERS_NUMBER];

	printf("Philosophers process created\n");

	//Creating forks
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		pthread_mutex_init(&forks[i], NULL);
	}	
	
	//Starting philosophers threads
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		philosophers_data[i] = i;
		pthread_create(&philosophers_id[i], NULL, &philosopher, &philosophers_data[i]);
	}

	//Waiting for philosophers
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		pthread_join(philosophers_id[i], NULL);
	}

	printf("Philosophers process terminated\n");
}

void * philosopher(void * id)
{
	int i;
	int philosopherId = *((int *) id);
	int first_fork;
	int second_fork;

	printf("Philosopher %d created\n", philosopherId);

	for(i = 0; i < MAX_ITERATIONS; ++i)
	{
		//Choosing forks order
		chooseForks(philosopherId, &first_fork, &second_fork);

		//Taking / waiting forks
		takeForks(philosopherId, first_fork, second_fork);
		
		//Eating
		eat(philosopherId);

		//Releasing forks
		releaseFork(philosopherId, first_fork, second_fork);
		
		//Thniking
		think(philosopherId);
	}

	printf("Philosopher %d terminated\n", philosopherId);
	return 0;
}

void chooseForks(int philosopherId, int * first_fork, int * second_fork)
{
	int tmp = rand() % 2;
	if(tmp == 0)
	{
		*first_fork = philosopherId;
		*second_fork = (philosopherId + 1) % PHILOSOPHERS_NUMBER;
	}
	else
	{
		*first_fork = (philosopherId + 1) % PHILOSOPHERS_NUMBER;
		*second_fork = philosopherId;
	}
}

void takeForks(int philosopherId, int first_fork, int second_fork)
{
	printf("(%d) Taking forks %d and %d\n", philosopherId, first_fork, second_fork);
	pthread_mutex_lock(&forks[first_fork]);
	pthread_mutex_lock(&forks[second_fork]);
}

void eat(int philosopherId)
{
	float time = (rand() % (MAX_EATING_TIME * 1000)) / 1000.0;
	printf("(%d) Eating %.2f seconds\n", philosopherId, time);
	sleep(time);
}

void releaseFork(int philosopherId, int first_fork, int second_fork)
{
	printf("(%d) Putting forks %d and %d\n", philosopherId, second_fork, first_fork);
	pthread_mutex_unlock(&forks[second_fork]);
	pthread_mutex_unlock(&forks[first_fork]);
}

void think(int philosopherId)
{
	float time = (rand() % (MAX_THINKING_TIME * 1000)) / 1000.0;
	printf("(%d) Sleeping %.2f seconds\n", philosopherId, time);
	sleep(time);
}

int main()
{
	philosophers_process();
	return 0;
}
