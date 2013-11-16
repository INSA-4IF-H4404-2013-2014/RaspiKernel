
#ifdef OS_LINUX
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#endif

#include "../generic/thread.h"
#include "../generic/sleep.h"

#include "philosophers.h"

void philosophers_process(void)
{
	int i;
	philosopher_data phi_data[PHILOSOPHERS_NUMBER];

	//Creating forks
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		generic_mutex_init(&forks[i]);
	}	

	//Starting philosophers threads
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
		//Initializing the philosopher data structure
		phi_data[i].phi_id = i;
		
#ifdef OS_RASP
		sync_sem_init(&(phi_data[i].sem_id), 0);
#else
		phi_data[i].sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0660);
		semctl(phi_data[i].sem_id, 0, SETVAL, 0);
#endif
		//Starting process
		generic_thread_create(&(phi_data[i].process_id), &philo_func, &phi_data[i]);
	}

	//Waiting for philosophers
	for(i = 0; i < PHILOSOPHERS_NUMBER; ++i)
	{
#ifdef OS_RASP
		sync_sem_wait(&(phi_data[i].sem_id));
#else
		pthread_join(phi_data[i].process_id, NULL);
#endif
	}
}

void sync_philosopher(void * args)
{
	int i, first_fork, second_fork, phi_id;
	philosopher_data * phi_data = (philosopher_data *) args;
	phi_id = phi_data->phi_id;

	//printf("Philosopher %d created\n", philosopherId);

	for(i = 0; i < MAX_ITERATIONS; ++i)
	{
		//Choosing forks order
		chooseForks(phi_id, &first_fork, &second_fork);

		//Taking / waiting forks
		takeForks(phi_id, first_fork, second_fork);

		//Eating
		eat();

		//Releasing forks
		releaseFork(phi_id, first_fork, second_fork);
		
		//Thniking
		think();
	}
#ifdef OS_RASP
	sync_sem_post(&(phi_data->sem_id), 1);
#endif
}

void * philosopher(void * args)
{
	sync_philosopher(args);
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
	generic_mutex_lock(&forks[first_fork]);
	generic_mutex_lock(&forks[second_fork]);
}

void releaseFork(int philosopherId, int first_fork, int second_fork)
{
	//TODO MANAGE DEADLOCKS
	if(philosopherId) {};
#ifndef OS_RASP
	printf("(%d) Releasing forks %d and %d\n", philosopherId, second_fork, first_fork);
#endif
	generic_mutex_unlock(&forks[second_fork]);
	generic_mutex_unlock(&forks[first_fork]);
}

void eat()
{
#ifndef OS_RASP
	float time = (rand() % ((int) (MAX_EATING_TIME * 1000))) / 1000.0;
	generic_sleep(time);
#endif
}

void think()
{
#ifndef OS_RASP
	float time = (rand() % ((int) (MAX_THINKING_TIME * 1000))) / 1000.0;
	generic_sleep(time);
#endif
}
