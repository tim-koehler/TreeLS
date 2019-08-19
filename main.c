#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct Options
{
    char path[PATH_MAX];
    int recursionDepth;
    bool colorless;
    bool all;
};
typedef struct Options Options;

const int PADDING = 2;

void run(char *path, int depth, Options *options);
void print(char*, int, int);

int main(int argc, char *argv[])
{
    Options options;
    options.colorless = false;
    options.recursionDepth = 0;
    options.all = false;

    if(argc > 2)
    {
        int opt; 
    
        while((opt = getopt(argc, argv, ":r:ca")) != -1)  
        {  
            switch(opt)  
            {  
                case 'r':  
                    options.recursionDepth = atoi(optarg);  
                    break;  
                case 'c':  
                    options.colorless = true;
                    break;
                 case 'a':  
                    options.all = true;
                    break;  
                case '?':  
                    printf("Help"); 
                    break;  
                default:
                    printf("Unknown argument: %c", opt);
                    return -1;
            }  
        }  
    
        if(optind != argc - 1)
        {      
            printf("To many arguments...\n");
            return -1;  
        }

        strcpy(options.path, argv[optind]);
    }
    else
    {
        if (getcwd(options.path, PATH_MAX) == NULL) 
        {
            perror("getcwd() error");
            return -1;
        }
        strcpy(options.path, argv[1]);
    }
    
    printf("%s\n", options.path);

    run(options.path, 0, &options);

    return 0;
}

void run(char *path, int depth, Options *options)
{
    DIR *dir;
    struct dirent *dentry;
    struct stat fileStat;

    if((dir = opendir(path)) == NULL)
        return;

    while(1)
    {
        dentry = readdir(dir);
        if(dentry == NULL)
            break;

        if(dentry->d_name[0] == '.')
        {
            if(options->all == true)
                print(dentry->d_name, depth, 1);

            continue;
        }

        char currentFilePath[strlen(path) + strlen(dentry->d_name + 2)];
        strcpy(currentFilePath, path);
        strcat(currentFilePath, "/");
        strcat(currentFilePath, dentry->d_name);

        stat(currentFilePath, &fileStat);

        if(S_ISDIR(fileStat.st_mode))
        {
            print(dentry->d_name, depth, 1);
            run(currentFilePath, depth + PADDING, options);
        }
        else
        {
            print(dentry->d_name, depth, 0);
        }
    }
    closedir(dir);
}

void print(char *name, int depth, int isDir)
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