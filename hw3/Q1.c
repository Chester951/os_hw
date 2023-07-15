#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL_POINTS 1000000 // Total number of random points to generate 
#define NUM_THREADS 5        // Number of threads to use
#define POINTS_PER_THREAD 1000 // Number of random points per threads

double points_in_circle = 0; // Global count of points falling within the circle
pthread_mutex_t lock;     // Mutex lock to protect the shared variable

void *generate_points(void *arg)
{
    int i;
    int local_count = 0;

    for(int i = 0; i < TOTAL_POINTS / NUM_THREADS; i++)
    {
        double x = (double) rand() / RAND_MAX;
        double y = (double) rand() / RAND_MAX;
        if (x * x + y * y <= 1.0)
        {
            local_count++;
        }
    }
    pthread_mutex_lock(&lock);
    points_in_circle += local_count;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main()
{
    int i;
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, generate_points, NULL);
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    double pi = 4.0 * points_in_circle / TOTAL_POINTS;
    printf("Estimated value of pi: %lf\n", pi);

    return 0;
}