#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#define PHILOSOPHERS_NUMBER 5
#define MAX_ITERATIONS 1000
#define MAX_EATING_TIME 1
#define MAX_THINKING_TIME 1

/*
Five silent philosophers sit at a table around a bowl of spaghetti. A fork is placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when he has both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it's not being used by another philosopher. After he finishes eating, he needs to put down both forks so they become available to others. A philosopher can grab the fork on his right or the one on his left as they become available, but can't start eating before getting both of them.

Eating is not limited by the amount of spaghetti left: assume an infinite supply.
*/

//gcc -W -Wall -o philosophers philosophers.c -lpthread

//Forks used by the philosophers
pthread_mutex_t forks[PHILOSOPHERS_NUMBER];

//Function starting the philosopher processes
void philosophers_process(void);

/*
Philosopher process, alternately eating and thinking.
A philosopher can only eat spaghetti when he has both left and right forks
*/
void * philosopher(void * n);

void chooseForks(int philosopherId, int * first_fork, int * second_fork);

void takeForks(int philosopherId, int first_fork, int second_fork);

void eat(int philosopherId);

void releaseFork(int philosopherId, int first_fork, int second_fork);

void think(int philosopherId);

#endif
