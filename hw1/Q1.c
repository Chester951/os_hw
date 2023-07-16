#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;

	// input a number if a number is smaller than 0, should run until input >0 number.
	int k;
	do
	{
		printf("Enter a number n (n>0) to run the Collatz conjecture  : ");
		scanf("%d", &k);
	} 
	while (k <= 0);

	pid = fork();
	if (pid == 0)
	{
		printf("In child process....\n");
		printf("%d ", k);

		while (k != 1)
		{
			// even  case
			if (k % 2 == 0)
			{
				k = k / 2;
			}
			// odd case
			else
			{
				k = 3 * k + 1;
			}
			printf("%d, ", k);
		}
		printf("\nChild Complete !\n");
	}
	else
	{
		printf("Parent is waiting on child process.... \n");
		wait(NULL);
		printf("Parent Complete !");
	}
	return 0;
}