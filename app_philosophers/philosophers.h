#ifndef _H_PHILOSOPHERS
#define _H_PHILOSOPHERS

#include "../generic/thread.h"

#define MAX_ITERATIONS 1000
#define PHILOSOPHERS_NUMBER 5

#ifdef OS_RASP
	#define philo_func sync_philosopher
#else
	#define philo_func philosopher
#endif

/*
 * Five silent philosophers sit at a table around a bowl of spaghetti. A fork is placed between each pair of adjacent philosophers.
 * 
 * Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when he has both left and right forks. Each fork can be held by only one  
 * philosopher and so a philosopher can use the fork only if it's not being used by another philosopher. After he finishes eating, he needs to put down both forks so they  
 * become available to others. A philosopher can grab the fork on his right or the one on his left as they become available, but can't start eating before getting both of  
 * them.
 * 
 * Eating is not limited by the amount of spaghetti left: assume an infinite supply.
*/

//gcc -W -Wall -o phil main.c philosophers.c -lpthread

/*
 * Philosopher data structure
 */
typedef struct philosopher_data_t
{
	//Process ID used by the system
	generic_thread_t process_id;
	
	//Philosopher ID
	generic_thread_t phi_id;
	
	//Semaphore used to notify the parent process of the current process' end
	generic_sem sem_id;
} philosopher_data;

//Forks used by the philosophers
generic_mutex forks[PHILOSOPHERS_NUMBER];

/*
 * Initializes n mutex
 * Creates n philosopher processes linked with their forks
 * Wait for them if they are threads
 */
void philosophers_process(void);

/*
 * Philosopher process, alternately eating and thinking, called on a RaspberryOS
 * A philosopher can only eat spaghetti when he has both left and right forks
 * @param n The philosopher id
 */
void sync_philosopher(void * n);

/*
 * Philosopher process, alternately eating and thinking, called on Linux
 * A philosopher can only eat spaghetti when he has both left and right forks
 * @param n The philosopher id
 */
void * philosopher(void * n);

/*
 * Set the first fork as the left one, and the second one as the right one
 * @param philosopherId The philosopher id
 * @param first_fork The first fork to lock. This variable will be modified
 * @param second_fork The second fork to lock. This variable will be modified
 */
void chooseForks(int philosopherId, int * first_fork, int * second_fork);

/*
 * Unlock the mutex corresponding to the specified forks
 * @param philosopherId The philosopher id
 * @param first_fork The first fork to lock.
 * @param second_fork The second fork to lock.
 */
void takeForks(int philosopherId, int first_fork, int second_fork);

/*
 * Sleep x random seconds
 */
void eat(int philosopherId);

/*
 * Unlock the mutex corresponding to the specified forks
 * @param philosopherId The philosopher id
 * @param first_fork The seconkd fork to unlock.
 * @param second_fork The first fork to unlock.
 */
void releaseForks(int philosopherId, int first_fork, int second_fork);

/*
 * Sleep y random seconds
 */
void think(int philosopherId);

#endif
