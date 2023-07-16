# Homework 2
## Problem 1 (Compute statistical values. [Q1.c](./Q1.c))
### 1.1 Description
Write a multithreaded program that computes various statistical values for a list of numbers.
```
Input: 90 81 78 95 79 72 85
Output: 
The average value is 82
The minimum vlaue is 72
The maximum value is 95
also determine median and standard deviation.
```
### 1.2 Create threads and wait thread to finish
```c
void *busy(void *ptr) 
{
    // ptr will point to "Hi"
    puts("Hello World");
    return NULL;
}
int main() 
{
    pthread_t id;
    /* create threads */
    // thread: a variable that will hold the id of the newly created thread.
    // attr: normally be NULL
    // start_routine: a pointer to a functioourn that we want to run. (function pointer)
    // arg: a pointer that will be given to our function. 
    pthread_create(&id, NULL, busy, "Hi");

    /* wait for our thread to finish  */
    // id: threads id
    // result: result will be null because the busy function returned null
    void *result;
    pthread_join(id, &result);
}
```
### 1.3 Results
Compile program
```
gcc -o Q1.o Q1.c -lm
```
Running result
![](https://drive.google.com/uc?export=view&id=1-BjXqu5-CxqbTree5DMh79TS7wdpww9h)

## Problem 2 (Multithreaded sorting application. [Q2.c](./Q2.c))
### 2.1 Description
A list of integers is divided into two smaller lists of equal size. Two separate threads sort each sublist using bubble sort. The two sublists are then merged by a third thread, which merges the two sublists into single list.
```
Input: 7, 12, 19, 3, 18, 4, 2, 6, 15, 8
Output: 2, 3, 4, 6, 7, 8, 12, 15, 18, 19
```

### 2.2 Program Ideas
```
// split the unsorted array into two list. 

// create two threads to sort two unsorted lists.
pthread_create(thread1, NULL, bubble_sort, param1);
pthread_create(thread2, NULL, bubble_sort, param2);
// wait for threads to finish
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

// create third thread to merge two sorted lists.
pthread_create(thread3, NULL, merge, param3);
// wait for third threads to finish
pthread_join(thread3, NULL);
```

### 2.3 Results
Compile program
```
gcc -o Q2.o Q2.c
```
Running result
![](https://drive.google.com/uc?export=view&id=1-D729NstP5uaFtYTb4JWkt6Xk5HOI9Vb)

## Reference
1. [Pthreads, Part 1: Introduction](https://github.com/angrave/SystemProgramming/wiki/Pthreads%2C-Part-1%3A-Introduction)