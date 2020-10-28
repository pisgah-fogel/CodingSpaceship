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

struct {
    char* output;
    char* binary;
} Args;

char default_output[] = "sim.xml";

// Parse command line arguments and fill struct Args accordingly
void parse_args(int argc, char** argv)
{
    Args.output = NULL;
    Args.binary = NULL;
    for (size_t i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (i+2 > argc) {
                    puts("\"-o\" must be followed by the output file name (or path)\n");
                    exit(1);
                }
                else if (Args.output != NULL) {
                    puts("\"-o\" should not be used twice\n");
                    exit(1);
                }
                Args.output = argv[i+1];
                i++;
            }
            else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                printf("argv[%d] = %s\n", i, argv[i]);
                puts("Usage: ./runtime <program to test> [-o <.xml output file>]\n");
                exit(0);
            }
            else {
                printf("Unrecognized option \"%s\"\n", argv[i]);
                exit(1);
            }
        }
        else {
            if (Args.binary != NULL) {
                // TODO: Enable multiple program to play against each others
                puts("Error: too many input program (command line arguments)\n");
                exit(1);
            }
            Args.binary = argv[i];
        }
        
    }

    if (Args.binary == NULL) {
        puts("Error: Please provide a program to test\n");
        exit(1);
    }
    if (Args.output == NULL) {
        printf("[i] Using default output file...\n");
        Args.output = default_output;
    }
    printf("[i] Output file is: %s\n", Args.output);
}

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
    } else {
        puts("[x] IO Error while reading from child process\n");
        return std::string();
    }
}

int main(int argc, char** argv) {
    
    parse_args(argc, argv);

    int outfd[2];
    int infd[2];

    // pipes for parent to write and read
    pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);
     
    if(!fork()) {
         char* argv[]={ &(*Args.binary), "-q", 0};

         printf("[.] Running: '%s'...\n", Args.binary);
 
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
 
        child_write("2^6\n");
  
        child_read();

        child_write("2^3\n");
  
        child_read();
    }

    return 0;
}