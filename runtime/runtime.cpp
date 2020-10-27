#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h>

#define NUM_PIPES          2
#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1

int pipes[NUM_PIPES][2];

#define READ_FD  0
#define WRITE_FD 1
 
#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )
 
#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

int main(int argc, char** argv) {
    int outfd[2];
    int infd[2];

    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);
     
    if(!fork()) {
        char *argv[]={ "/usr/bin/bc", "-q", 0};
 
        dup2(CHILD_READ_FD, STDIN_FILENO);
        dup2(CHILD_WRITE_FD, STDOUT_FILENO);
 
        /* Close fds not required by child. Also, we don't
           want the exec'ed program to know these existed */
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);
          
        execv(argv[0], argv);
    } else {
        char buffer[100];
        int count;
 
        /* close fds not required by parent */       
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
 
        // Write to child’s stdin
        write(PARENT_WRITE_FD, "2^32\n", 5);
  
        // Read from child’s stdout
        count = read(PARENT_READ_FD, buffer, sizeof(buffer)-1);
        if (count >= 0) {
            buffer[count] = 0;
            printf("%s", buffer);
        } else {
            printf("IO Error\n");
        }
    }

    return 0;
}