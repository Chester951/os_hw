# Homework 3
## Problem
### Descriptions
You were asked to create five threads that geneate 1,000 random points and deciding the points whether fall in the circle. Storing this result in a global variable. In main threads compute  $\pi$ by foumla $ 4*\frac {points\, in\, circle} {total\, points} $.
### Compute $\pi$ by Monte Carlo method
Equation can be refer to [Link](https://youtu.be/ELetCV_wX_c).

### Mutex locks
#### What is a Critical Section
A cirtical section is a section of code that can only be executed by one threads at a time. If two threads were to execute code inside the critical section at the same time then it is possible that program may no loger have correct behavior.

#### How to ensure only one thread at a time can access a global variable?
Just add thee lines:
``` c
pthread_mutex_t lock;       // global variable
pthread_mutex_lock(&lock);  // start of critical section 
pthread_mutex_unlock(&lock); // end of critical section 
```
As soon as the original thread unlocks the mutex, the secound (waiting) thread will acquire the lock and be able to continue.

#### Other ways to create a mutex

``` c
pthread_mutex_t *lock = malloc(sizeof(pthread_mutex_t));       
pthread_mutex_init(lock, NULL);  
// later
// we must have equal of unlocks and locks in an execution
pthread_mutex_destroy(lock);
free(lock);
```

## Reference
