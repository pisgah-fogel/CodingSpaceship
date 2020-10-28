/**
 * @file Engine.hpp
 * @author Phileas Fogg
 * @brief Communication between the child process(es) and the game
 * @version 0.1
 * @date 2020-10-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <cstring>
#include <string>
#include <unistd.h>

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

// Write to child’s stdin
void child_write(std::string str) {
    write(PARENT_WRITE_FD, str.c_str(), str.size());
}

// Read from child’s stdout
std::string child_read() {
    char buffer[100];
    int count;
    count = read(PARENT_READ_FD, buffer, sizeof(buffer)-1);
    if (count > 0) {
        buffer[count] = 0;
        printf("> %s", buffer);
        return std::string(buffer);
    } else if (count == 0) {
        puts("> [empty]\n");
        return std::string();
    } else {
        puts("[x] IO Error while reading from child process\n");
        return std::string();
    }
}

typedef struct {
    char* output;
    char* binary;
    void (*main)();
} Args;

void child_run(Args* arguments) {
    int outfd[2];
    int infd[2];

    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);
     
    if(!fork()) {
         char* argv[]={ &(*arguments->binary), "-q", 0};

         printf("[.] Running: '%s'...\n", arguments->binary);
 
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
        /* close fds not required by parent */       
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);

        if (arguments->main != NULL) {
            (*arguments->main)();
        }
        else {
            puts("[x] Error: No main game function to run.\n");
        }
    }
}