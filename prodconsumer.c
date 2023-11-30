#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define buffer_size 10

int count=0;
int in=0;
int out=0;
int buffer[buffer_size];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
    int item;
    for(int i=0;i<10;i++)
    {
        item=rand()%100;             //produced item
        pthread_mutex_lock(&mutex);  //lock acquired
        while(count==buffer_size)
        {
            pthread_cond_wait(&empty, &full);   //wait 
        }
        buffer[in]=item;
        printf("Produced Item: %d",item);
        in=(in+1)%buffer_size;
        count++;

        pthread_cond_signal(&full);     //signals threads which were blocked under the full condition
        pthread_mutex_unlock(&mutex);  //release lock

    }
pthread_exit(NULL);
}

void *consumer(void *arg)
{
    for(int i=0;i<10;i++)
    {
    int item;
    pthread_mutex_lock(&mutex);
    while(count==0)
    {
        pthread_cond_wait(&full, &mutex);
    }
    item=buffer[out];
    out=(out+1)%buffer_size;
    printf("Consumed Item: %d", item);
    count--;

    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);

}
pthread_exit(NULL);
}


int main()
{
    pthread_t pt,ct;
    pthread_create(&pt,NULL,producer,NULL);
    pthread_create(&ct,NULL,consumer,NULL);

    pthread_join(pt,NULL);
    pthread_join(ct,NULL);

}