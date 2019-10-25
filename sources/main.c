#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "status_information_scanner.h"
#include "awesomepsio.h"

long parsePID(char *str)
{
    char *endptr;
    long pid = strtol(str, &endptr, 10);
    if (errno == ERANGE)
    {
        printf("PID parsing error: the resulting value was out of range.\n");
        exit(-1);
    }
    if (endptr == str || *endptr != '\0')
    {
        printf("PID parsing error: '%s' could not be parsed.\n", str);
        exit(-1);
    }
    return pid;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: ps <pid>\n");
        return 1;
    }
    long pid = parsePID(argv[1]);
    status_information information;
    if (scanStatusInformation(pid, &information) == -1)
    {
        printf("PID not found: no /proc/%d/stat virtual file was found.\n", pid);
        exit(-2);
    }
    else
    {
        printFullStatusInformation(&information);
    }
    return 0;
}
