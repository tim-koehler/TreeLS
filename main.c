#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

const int PADDING = 4;
int prevDepth = 0;

void runn(char *path, int depth);
void print(char*, int);
void printFooter();

int main(int argc, char** argv)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {
       perror("getcwd() error");
       return 1;
    }

    printf("%s\n", cwd);

    runn(".", 0);
    printFooter();

    return 0;
}

void runn(char *path, int depth)
{
    struct dirent* dentry;
    DIR *dir;

    if((dir = opendir(path)) == NULL)
        return;

    while(1)
    {
        dentry = readdir(dir);
        if(dentry == NULL)
            break;

        if(dentry->d_name[0] == '.')
            continue;
        
        print(dentry->d_name, depth);

        char *newPath = (char*) calloc(sizeof(char), strlen(path) + 1 + strlen(dentry->d_name) + 1);
        strcpy(newPath, path);
        strcat(newPath, "/");
        strcat(newPath, dentry->d_name);
        runn(newPath, depth + PADDING);
        free(newPath);
    }
    closedir(dir);
}

void print(char *name, int depth)
{
    printf("\u251C");
    
    for (size_t i = 0; i < depth; i++)
    {
        printf("\u2500");
    }

    printf("\u2500 %s (%d/%d)\n", name, prevDepth, depth);

    prevDepth = depth;
}


void printFooter()
{
    printf("\u2518");
}