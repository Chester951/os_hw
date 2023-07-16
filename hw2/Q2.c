#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
int array[ARRAY_SIZE] = {9, 4, 7, 2, 5, 8, 3, 1,6,0};
int sorted[ARRAY_SIZE];

typedef struct {
    int start_index;
    int end_index;
}SortParams;


// bubble sort function
void* bubble_sort(void* arg)
{
    SortParams* params = (SortParams*) arg;
    int i, j;
    for (int i = params->start_index; i < params->end_index; i++)
    {
        for (int j = params->start_index; j < params->end_index - i + params->start_index; j++)
        {
            if (array[j] > array[j+1])
            {
                int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
    pthread_exit(NULL);
}

// merge sort function
void* merge(void* arg)
{
    SortParams* params = (SortParams*) arg;
    int i = params->start_index;
    int mid = (params->start_index + params->end_index) / 2;
    int j = mid + 1;
    int k = 0;

    // we want to merge two sorted array
    // if array[i] < array[j] then passed array[i] value into sorted[k]
    // else passed array[j] value into sorted[k]
    while (i <= mid && j <= params->end_index)
    {
        if (array[i] < array[j])
        {
            sorted[k++] = array[i++];
        }
        else
        {
            sorted[k++] = array[j++];
        }
    }
    // if there are values still in array[i] 
    // it means the rest array[i] values is larger than array[j]
    // pass the rest values to sorted[k] 
    while (i <= mid)
    {
        sorted[k++] = array[i++];
    }
    // if there are values still in array[j] 
    // it means the rest array[j] values is larger than array[i]
    // pass the rest values to sorted[k] 
    while (j <= params->end_index)
    {
        sorted[k++] = array[j++];
    }
    
    pthread_exit(NULL);
}


int main()
{
    pthread_t thread1, thread2, thread3;
    SortParams params1 = {0, ARRAY_SIZE / 2 - 1};
    SortParams params2 = {ARRAY_SIZE / 2, ARRAY_SIZE - 1};
    SortParams params3 = {0, ARRAY_SIZE - 1};

    // seperate the unsorted array into two threads.
    pthread_create(&thread1, NULL, bubble_sort, &params1);
    pthread_create(&thread2, NULL, bubble_sort, &params2);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // merge two sorted array finished from two threads.
    pthread_create(&thread3, NULL, merge, &params3);
    pthread_join(thread3, NULL);

    int i;
    printf("Before Sorted Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("After Sorted Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    
    return 0;
}