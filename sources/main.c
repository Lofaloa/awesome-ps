#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#include "process_selector.h"

int main(int argc, char **argv)
{
    int pids[1000];
    searchProcesses(pids);
    int current = 0;
    while (pids[current] != NULL)
    {
        printf("%d\n", pids[current]);
        current++;
    }
    return 0;
}
