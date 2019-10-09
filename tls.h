#include <stdbool.h>
#include <linux/limits.h>

struct Options
{
    char path[PATH_MAX];
    int recursionDepth;
    bool all;
};
typedef struct Options Options;

void run(char *path, int depth, Options *options);
int parseOptions(int argc, char *argv[],  Options *options);