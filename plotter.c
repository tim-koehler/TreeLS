#include "plotter.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void printLine(char *name, int depth, int isDir)
{
    for (size_t i = 0; i < depth; i++)
    {
        if((i % 2) == 0)
            printf("\u2502");
        else
            printf(" ");
    }

    printf("\u251C");
    
    if(isDir == 1)
    {
        printf(ANSI_COLOR_BLUE);
        printf(" %s\n", name);
        printf(ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_YELLOW);
        printf(" %s\n", name);
        printf(ANSI_COLOR_RESET);
    }
}