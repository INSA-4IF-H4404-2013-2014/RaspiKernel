#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#ifdef OS_RASP
	#include "os/api_process.h"
	#include "os/api_sync_mutex.h"

	#define phi_mutex sync_mutex_t
	#define phi_mutex_init(mutex) sync_mutex_init(mutex)
	#define phi_mutex_lock(mutex) sync_mutex_lock(mutex)
	#define phi_mutex_unlock(mutex) sync_mutex_unlock(mutex)
	#define phi_id uint32_t
#else
	#include <pthread.h>

	#define phi_mutex pthread_mutex_t
	#define phi_mutex_init(mutex) pthread_mutex_init(mutex, NULL)
	#define phi_mutex_lock(mutex) pthread_mutex_lock(mutex)
	#define phi_mutex_unlock(mutex) pthread_mutex_unlock(mutex)
	#define phi_id pthread_t
#endif

#define PHILOSOPHERS_NUMBER 5
#define MAX_ITERATIONS 1000
#define MAX_EATING_TIME 1
#define MAX_THINKING_TIME 1

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

//gcc -W -Wall -o phil philosophers.c -lpthread

//Forks used by the philosophers
phi_mutex forks[PHILOSOPHERS_NUMBER];

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
void eat();

/*
 * Unlock the mutex corresponding to the specified forks
 * @param philosopherId The philosopher id
 * @param first_fork The seconkd fork to unlock.
 * @param second_fork The first fork to unlock.
 */
void releaseFork(int philosopherId, int first_fork, int second_fork);

/*
 * Sleep y random seconds
 */
void think();

#endif
