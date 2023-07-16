# Homework 1
## Problem 1 (Collatz conjecture. [Q1.c](./3.14_Collatz_conjecture.c))
### 1.1 Collatz conjecture 
Collatz conjecture take any positive integer n and apply the following algorithm.
$$n =\begin{cases}n/2, & \text{if n is even} \\3\times n+1, & \text{if n is odd}\end{cases}$$

### 1.2 Descriptions
Using the `fork()` system call to generate the sequence of child process. User should provide the starting number in command line.
```
Input: 8
Output: 8,4,2,1
Explanation: If 8 is passed, the child process will output the collatz conjecture result
``` 

### 1.3 Parent process and child process
``` c
pid_t child_id = fork();
if (child_id == 0) 
{
    // In child...
    // start calculation
    exit(123);
}
else
{
    // we have a child! Get their exit code
    wait(NULL);
}

```
### 1.4 Results
Compile program
```
gcc -o Q1.o Q1.c
```
Running result

![](https://drive.google.com/uc?export=view&id=1-3INItUJVo4KUQjF-x3s4gl3ZxXtRRmK)


## Problem 2 (Collatz conjecture with share memory. [Q2.c](./3.15_Collatz_conjecture_share_memory.c))
### 2.1 Descriptions
In Problem 1, the child process must output the sequence of numbers generated from the algorithm specified by the Collatz conjecture because the parent and child have their own copies of the data. 

Another approach is to design a program to establish a shared memory object between the parent and child processes. This technique allows the child to write the contents of the sequence when the child completes.  
```
Input: 8
Output: 8,4,2,1
Explanation: If 8 is passed, the shared memory object stores the collatz conjecture result.
``` 

### 2.2 Create share memory object
Shared memory allows multiple processes to access a common memory region (Buffer). It enables inter-process communication and data sharing.

#### 2.2.1 Share memory pointer
```c
// shm_open(): request a shared memory segment.
shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
// ftruncate(): set the size of the shared memory segment.
ftruncate(shm_fd, SIZE);
// mmap(): obtain a pointer to the shared memory region.
ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);  
```

#### 2.2.2 Fail to create child process
If the child process fails to create, output the error message and release the shared memory.
```c
if (pid < 0)
{
    fprintf(stderr, "Fork Failed\n");
	shm_unlink(name); // name is share memory's name
	return 1;
}
```
#### 2.2.3 Success to create child process

```c
else if (pid == 0)
{
	// In child process
	// Create buffer in child process to write the result and set buffer to 0
    char buffer[BUFFER_SIZE];
	memset(buffer, 0, sizeof(char) * BUFFER_SIZE);
	// pointer to the head of buffer
	char *buffer_p = &buffer[0];
	buffer_p += sprintf(buffer_p, "%d,", k);
    // Compute the Collatz conjecture and store in buffer_p 
    // ....
    // sprintf(): Copy the contents of buffer to share memory area
	sprintf(ptr, "%s,", buffer);
	printf("\nChild Complete! The data to shared memory has written.\n");
}
```
#### 2.2.4 In parent process

```c
else
{
	wait(NULL);
	printf("Reading the shared memory\n");
	// shm_open(): Open the created share memory area in read-only mode.
	shm_fd = shm_open(name, O_RDONLY, 0666);
	// mmap(): Map shared memory area into its own address in read-only mode.
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 
	// print the result
	printf("%s", (char *)ptr);
	// Delete the shared memory object, system will automatically release the shared memory area.
	shm_unlink(name);
}
```

### 2.3 Result
Compile program
```
gcc -o 3.15_Collatz_conjecture_share_memory.out 3.15_Collatz_conjecture_share_memory.c 
```

Running result

![](https://drive.google.com/uc?export=view&id=1-6fN7-jqc0nXkfoXWztEQknML8Bv2YTI)


## Problem 3 (Copy .txt file. [Q3.c](./3.20_filecopy.c))
### 3.1 Descriptions

Design a file copying program using ordinary pipes. This program will be passed two parameters. For example:
```
cmd: ./filecopy.o input.txt output.txt
Output: output.txt
Explanatin: The output.txt should appear the text which is same as input text.
```
### 3.2 Create pipe and use pipe to communicate with a child process
Create the pipe before forking.
```c
int fd[2];
pipe(fd);
pid_t pid = fork()

if (pid == 0)
{
	/* In child process (Read the data from pipe and wite data to dst.txt) */
	// Close the write end of the pipe
	close(fd[WRITE_END]);
	// Read from the pipe and write to the destination file
	
}
else 
{
	/* In parent process (Read the data from src.txt and write data to pipes) */
	// Close the read end of the pipe
	close(fd[READ_END]); 	
	// Read from the src.txt and write to the pipe
	char buffer[80];
}

```

### 3.3 Results
Compile program
```
gcc -o 3.20_filecopy.o 3.20_filecopy.c
```

Running result

![](https://drive.google.com/uc?export=view&id=1-B7xCHiZlxE3SsFlGSdrI1iUiXAnhNGw)


## Reference
1. [Forking, Part 1: Introduction](https://github.com/angrave/SystemProgramming/wiki/Forking%2C-Part-1%3A-Introduction)
2. [Insert google drive photos](https://hackmd.io/@Jujubeleven/r1kubA4ps)