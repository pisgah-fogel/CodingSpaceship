#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <cstring>
#include <string>
#include <unistd.h>

#include "Engine.hpp"
#include "Game.hpp"

char default_output[] = "sim.xml";

// Parse command line arguments and fill struct Args accordingly
Args* parse_args(int argc, char** argv)
{
    Args* arguments = (Args*)malloc(sizeof(Args));
    arguments->output = NULL;
    arguments->binary = NULL;
    for (size_t i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (i+2 > argc) {
                    puts("\"-o\" must be followed by the output file name (or path)\n");
                    exit(1);
                }
                else if (arguments->output != NULL) {
                    puts("\"-o\" should not be used twice\n");
                    exit(1);
                }
                arguments->output = argv[i+1];
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
            if (arguments->binary != NULL) {
                // TODO: Enable multiple program to play against each others
                puts("Error: too many input program (command line arguments)\n");
                exit(1);
            }
            arguments->binary = argv[i];
        }
        
    }

    if (arguments->binary == NULL) {
        puts("Error: Please provide a program to test\n");
        exit(1);
    }
    if (arguments->output == NULL) {
        printf("[i] Using default output file...\n");
        arguments->output = default_output;
    }
    printf("[i] Output file is: %s\n", arguments->output);
    return arguments;
}

int main(int argc, char** argv) {
    
    Args* arguments = parse_args(argc, argv);
    arguments->main = &main_game;

    child_run(arguments);

    delete(arguments);
    puts("[v] Resources freed.");
    return 0;
}