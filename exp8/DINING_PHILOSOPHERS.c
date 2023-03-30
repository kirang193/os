#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t chopstick[5];
void eat(int ph)
{
    printf("Philosopher %d begins to eat.\n", ph);
}
void *philos(void *n)
{
    int ph = *(int *)n;
    printf("Philosopher %d wants to eat.\n", ph);
    printf("Philosopher %d tries to pick left chopstick.\n", ph);
    sem_wait(&chopstick[ph]);
    printf("Philosopher %d picks the left chopstick.\n", ph);
    printf("Philosopher %d tries to pick right chopstick.\n", ph);
    sem_wait(&chopstick[(ph + 1) % 5]);
    printf("Philosopher %d picks the right chopstick.\n", ph);
    eat(ph);
    sleep(2);
    printf("Philosopher %d has finished eating. ✓\n", ph);
    sem_post(&chopstick[(ph + 1) % 5]);
    printf("Philosopher %d leaves the right chopstick.\n", ph);
    sem_post(&chopstick[ph]);
    printf("Philosopher %d leaves the left chopstick.\n", ph);
}

int main()
{
    int i, n[5];
    pthread_t thrd[5];
    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);
    for (i = 0; i < 5; i++)
    {
        n[i] = i;
        pthread_create(&thrd[i], NULL, philos, (void *)&n[i]);
    }
    for (i = 0; i < 5; i++)
        pthread_join(thrd[i], NULL);
}
/*sem_init: This initializes the semaphore *sem. The initial value of the semaphore will be value. 
If pshared is 0, the semaphore is shared among all threads of a process.
If pshared is not zero, the semaphore is shared but should be in shared memory.*/

/*sem_destroy(): Unallocates the semaphore(destroy).
On success, the return value is 0,
On failure, the return value is -1.*/

/*sem_post(&sem): increments the semaphore by 1.
On success, the return value is 0,
On failure, the return value is -1.
*/
