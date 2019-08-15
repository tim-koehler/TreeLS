#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const int PADDING = 2;

void run(char *path, int depth);
void print(char*, int);

int main(int argc, char *argv[])
{
    char path[PATH_MAX];
    
    if(argc == 2)
    {
        strcpy(path, argv[1]);
    }
    else
    {
        if (getcwd(path, sizeof(path)) == NULL) 
        {
            perror("getcwd() error");
            return 1;
        }
    }

    printf("%s\n", path);

    run(path, 0);

    return 0;
}

void run(char *path, int depth)
{
    struct dirent* dentry;
    DIR *dir;

    if((dir = opendir(path)) == NULL)
    {
        return;
    }

    while(1)
    {
        dentry = readdir(dir);
        if(dentry == NULL)
            break;

        if(dentry->d_name[0] == '.')
            continue;
        
        print(dentry->d_name, depth);

        // Two extra byte for '/' and '\0'
        char *newPath = (char*) calloc(sizeof(char), strlen(path) + 1 + strlen(dentry->d_name) + 1);
        strcpy(newPath, path);
        strcat(newPath, "/");
        strcat(newPath, dentry->d_name);
        run(newPath, depth + PADDING);
        free(newPath);
    }
    closedir(dir);
}

void print(char *name, int depth)
{
    for (size_t i = 0; i < depth; i++)
    {
        if((i % 2) == 0)
            printf("\u2502");
        else
            printf(" ");
    }

    printf("\u251C");
    
    printf("\033[1;34m");
    printf(" %s\n", name);
    printf("\033[0m");
}