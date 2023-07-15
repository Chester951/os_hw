// Compile the file  gcc -o Q1.o Q1.c -lm
// Run the file ./Q1.o 1 2 3 4 5...

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Global variable for storing result.
double average, median, stddev;
int minimum, maximum;


int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void* compute_average(void* arg)
{
    int *numbers = (int*) arg;
    int argc = *(int*) numbers; // Extract argc from the first element of the array.
    int sum = 0;
    for (int i = 1; i < argc; i++)
    {
        sum += numbers[i];
    }
    average = (double) sum / (argc - 1); // Divide by (argc - 1) to exclude the first element.
    pthread_exit(NULL);
}

void* compute_minimum(void* arg)
{
    int *numbers = (int*) arg;
    int argc = *(int*) numbers; // Extract argc from the first element of the array.
    minimum = numbers[1];
    for (int i = 2; i < argc; i++)
    {
        if (numbers[i] < minimum)
        {
            minimum = numbers[i];
        } 
    }
    pthread_exit(NULL);
}

void* compute_maximum(void* arg)
{
    int *numbers = (int*) arg;
    int argc = *(int*) numbers; // Extract argc from the first element of the array.
    maximum = numbers[1];
    for (int i = 2; i < argc; i++)
    {
        if (numbers[i] > maximum)
        {
            maximum = numbers[i];
        } 
    }
    pthread_exit(NULL);
}

void* compute_median(void* arg)
{
    int *numbers = (int*) arg;
    int argc = *(int*) numbers; // Extract argc from the first element of the array.
    int *sorted = (int*) malloc((argc - 1) * sizeof(int));
    for (int i = 1; i < argc; i++)
    {
        sorted[i - 1] = numbers[i];
    }
    qsort(sorted, argc - 1, sizeof(int), cmpfunc);

    if ((argc - 1) % 2 == 0)
    {
        int mid = (argc - 1) / 2;
        median = (double) (sorted[mid] + sorted[mid - 1]) / 2;
    }
    else
    {
        int mid = (argc - 1) / 2;
        median = sorted[mid];
    }
    free(sorted);
    pthread_exit(NULL);
}

void* compute_stddev(void* arg)
{
    int *numbers = (int*) arg;
    int argc = *(int*) numbers; // Extract argc from the first element of the array.
    double sum = 0;
    for (int i = 1; i < argc; i++)
    {
        sum += pow(numbers[i] - average, 2);
    }
    stddev = sqrt(sum / (argc - 2));
    pthread_exit(NULL);
}




int main(int argc, char *argv[])
{
    // check the input variable is correct
    if (argc < 2)
    {
        printf("Usage: %s number1 [number2 ...]\n", argv[0]);
        return 1;
    }

    // Convert the command line arguments to integers
    int *numbers = (int *) malloc((argc - 1) * sizeof(int));
    for (int i = 1; i < argc; i++)
    {
        numbers[i] = atoi(argv[i]);
    }
    numbers[0] = argc; // pass argc as the first element of the array.

    // Create the worker threads
    pthread_t threads[5];
    pthread_create(&threads[0], NULL, compute_average, (void*) numbers);
    pthread_create(&threads[1], NULL, compute_minimum, (void*) numbers);
    pthread_create(&threads[2], NULL, compute_maximum, (void*) numbers);
    pthread_create(&threads[3], NULL, compute_median, (void*) numbers);
    pthread_create(&threads[4], NULL, compute_stddev, (void*) numbers);

    // Wait for the worker threads to finish
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Output the results
    printf("The average value is %f\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);
    printf("The midian value is %f\n", median);
    printf("The stddev value is %f\n", stddev);

    free(numbers);

    return 0;
}