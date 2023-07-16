# Homework 3
## Problem 1
### 1.1 Descriptions
You were asked to create five threads that geneate 1,000 random points and deciding the points whether fall in the circle. Storing this result in a global variable. In main threads compute  $\pi$ by foumla $ 4*\frac {points\, in\, circle} {total\, points} $.
```
Output: computed pi value
Explanation: create another 5 threads and each thread generate 1,000 points and by using Monte Carlo method to compute pi.
```

### 1.2 Compute $\pi$ by Monte Carlo method
Equation can be refer to [Link](https://youtu.be/ELetCV_wX_c).

### 1.3 Mutex locks
#### 1.3.1 What is a Critical Section
A cirtical section is a section of code that can only be executed by one threads at a time. If two threads were to execute code inside the critical section at the same time then it is possible that program may no loger have correct behavior.

#### 1.3.2 How to ensure only one thread at a time can access a global variable?
Just add thee lines:
``` c
pthread_mutex_t lock;       // global variable
pthread_mutex_lock(&lock);  // start of critical section 
pthread_mutex_unlock(&lock); // end of critical section 
```
As soon as the original thread unlocks the mutex, the secound (waiting) thread will acquire the lock and be able to continue.

#### 1.3.3 Other ways to create a mutex

``` c
pthread_mutex_t *lock = malloc(sizeof(pthread_mutex_t));       
pthread_mutex_init(lock, NULL);  
// later
// we must have equal of unlocks and locks in an execution
pthread_mutex_destroy(lock);
free(lock);
```

### 1.4 Results
Compile program
```
gcc -o Q1.o Q1.c
```

## Reference
1. [Synchronization, Part 1: Mutex Locks](https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-1%3A-Mutex-Locks)
