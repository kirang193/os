#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
8. Implement Producer-consumer problem
*/

#define MaxItems 10 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 10 // Size of the buffer
#define num_items 100
// I've used 10 consumers and 10 producers here.
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%(num_items)+1; // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Inserted Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Removed Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{

    pthread_t prodcr[10],consmr[10];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int arr[10];
    for(int i=0;i<10;i++){
        arr[i] = i+1;
    }

    for(int i = 0; i < 10; i++) {
        pthread_create(&prodcr[i], NULL, (void *)producer, (void *)&arr[i]);
    }
    for(int i = 0; i < 10; i++) {
        pthread_create(&consmr[i], NULL, (void *)consumer, (void *)&arr[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(prodcr[i], NULL);
    }
    for(int i = 0; i < 10; i++) {
        pthread_join(consmr[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


/*sem_init: This initializes the semaphore *sem. The initial value of the semaphore will be value. 
If pshared is 0, the semaphore is shared among all threads of a process.
If pshared is not zero, the semaphore is shared but should be in shared memory.*/

/*sem_destroy(): Unallocates the semaphore(destroy).
On success, the return value is 0,
On failure, the return value is -1.*/

/*
pthread_mutex_init(pthread_mutex_t *mutex, 
    const pthread_mutexattr_t *attr): Initialized a mutex
pthread_mutex_destroy(&mutex): Destroys mutex.
*/
