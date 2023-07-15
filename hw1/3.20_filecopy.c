#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>    // for 0_* constant
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 50
#define READ_END 0
#define WRITE_END 1



int main(int argc, char* argv[])
{
    // file descriptor, fd[0] is thr read end, fd[1] is the write end
    int fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    ssize_t nread;
    int source_fd, dest_fd;

    if (argc != 3)
    {
        printf("Operating System Homework 1\n");
        printf("Filecopy Program\n");
        printf("At least need 2 params\n");
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // create a pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // inside the child process
        printf("In the child process\n");
        // close the write end of the pipe
        close(fd[WRITE_END]);
        
        // open the destination file
        // O_WRONLY is open file in write mode.
        // O_CREAT is create file if the file not exist.
        // O_TRUNC is if file exist than set the file to the new one.
        dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
        if (dest_fd == -1)
        {
            perror("open file");
            exit(EXIT_FAILURE);
        }
        
        // read from the pipe and write to the destination file
        while ((nread = read(fd[0], buffer, BUFFER_SIZE)) > 0)
        {
            if (write(dest_fd, buffer, nread) != nread)
            {
                perror("write file");
                exit(EXIT_FAILURE);
            };
        }
        if (nread == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        close(dest_fd);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // inside the parent process
        printf("Parent sending message\n");

        // colse the read end of the pipe
        close(fd[READ_END]); 
        
        // open the source file
        source_fd = open(argv[1], O_RDONLY); // O_RDONLY is read only
        if (source_fd == -1)
        {
            perror("open file");
            exit(EXIT_FAILURE);
        }
        
        // read from the source file and write to the pipe
        while ((nread = read(fd[0], buffer, BUFFER_SIZE)) > 0)
        {
            if (write(fd[1], buffer, nread) != nread)
            {
                perror("write file");
                exit(EXIT_FAILURE);
            };
        }
        if (nread == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        close(source_fd);
        exit(EXIT_SUCCESS);
    }
    return 0;
}
