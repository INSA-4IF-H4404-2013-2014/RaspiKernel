#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "philosophers.h"

void philosophers_process(void)
{
	int i;
	phi_id philosophers_id[PHILOSOPHERS_NUMBER];
	int philosophers_data[PHILOSOPHERS_NUMBER];

	//Creating forks
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		phi_mutex_init(&forks[i]);
	}	

	//Starting philosophers threads
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		philosophers_data[i] = i;
#ifdef OS_RASP
		philosophers_id[i] = process_create(&sync_philosopher, &philosophers_data[i]);
		process_start(philosophers_id[i]);
#else
		pthread_create(&philosophers_id[i], NULL, &philosopher, &philosophers_data[i]);
#endif
	}

#ifndef OS_RASP
	//Waiting for philosophers
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		pthread_join(philosophers_id[i], NULL);
	}
#endif
}

void sync_philosopher(void * id)
{
	int i;
	int philosopherId = *((int *) id);
	int first_fork;
	int second_fork;

	//printf("Philosopher %d created\n", philosopherId);

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
}

void * philosopher(void * n)
{
	sync_philosopher(n);
	return 0;
}

void chooseForks(int philosopherId, int * first_fork, int * second_fork)
{
/*
	if(RANDOM_FORKS == 1 && rand() % 2 == 0)
	{
			*first_fork = philosopherId;
			*second_fork = (philosopherId + 1) % PHILOSOPHERS_NUMBER;
	}
	else
*/
	*first_fork = (philosopherId + 1) % PHILOSOPHERS_NUMBER;
	*second_fork = philosopherId;
}

void takeForks(int philosopherId, int first_fork, int second_fork)
{
	//TODO MANAGE DEADLOCKS
	if(philosopherId) {};
#ifndef OS_RASP
	printf("(%d) Taking forks %d and %d\n", philosopherId, first_fork, second_fork);
#endif
	phi_mutex_lock(&forks[first_fork]);
	phi_mutex_lock(&forks[second_fork]);
}

void releaseFork(int philosopherId, int first_fork, int second_fork)
{
	//TODO MANAGE DEADLOCKS
	if(philosopherId) {};
#ifndef OS_RASP
	printf("(%d) Releasing forks %d and %d\n", philosopherId, second_fork, first_fork);
#endif
	phi_mutex_unlock(&forks[second_fork]);
	phi_mutex_unlock(&forks[first_fork]);
}

void eat()
{
#ifndef OS_RASP
	float time = (rand() % (MAX_EATING_TIME * 1000)) / 1000.0;
	sleep(time);
#endif
}

void think()
{
#ifndef OS_RASP
	float time = (rand() % (MAX_THINKING_TIME * 1000)) / 1000.0;
	sleep(time);
#endif
}
