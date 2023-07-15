#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // for ftruncate
#include <wait.h>     // for wait
#include <sys/mman.h> // for shm_open
#include <fcntl.h>    // for 0_* constant
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	// input a number
	int k;
	do
	{
		printf("Enter a number n (n>0) to run the Collatz conjecture  : ");
		scanf("%d", &k);
	} 
	while (k <= 0);

	// create a share memory area
	const int SIZE = 4096;
	const char *name = "OS";
	const int BUFFER_SIZE = 1024;
	int shm_fd;
	void *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);				// Truncate the file
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); // map the file into memory

	// create the process
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork Failed\n");
		shm_unlink(name);
		return 1;
	}
	else if (pid == 0)
	{
		printf("In child process.");
		
		// child process
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, sizeof(char) * BUFFER_SIZE);
		char *buffer_p = &buffer[0];
		buffer_p += sprintf(buffer_p, "%d,", k);

		while (k != 1)
		{
			// even  case
			if (k % 2 == 0)
			{
				k = k / 2;
				buffer_p += sprintf(buffer_p, "%d,", k);
			}
			// odd case
			else
			{
				k = 3 * k + 1;
				buffer_p += sprintf(buffer_p, "%d,", k);
			}
		}
		sprintf(ptr, "%s,", buffer);
		printf("\nChild Complete! The data to shared memory has written.\n");
	}
	else
	{
		printf("Parent is waiting on child process.\n");
		wait(NULL);
		printf("Reading the shared memory\n");
		shm_fd = shm_open(name, O_RDONLY, 0666);
		ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); // map the file into memory
		printf("%s", (char *)ptr);
		shm_unlink(name);
	}
	return 0;
}