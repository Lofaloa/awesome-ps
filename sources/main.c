#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "status_information_scanner.h"
#include "process_selector.h"
#include "awesomepsio.h"

/**
 * Parses a string representing a pid and convert it to a long integer. The
 * value of the parsed pid is returned.
 * 
 * The given string should exclusively contain numerical characters. If it not
 * the case, this functions exits the program and prints a appropriate message
 * 
 * If the represented pid is evaluated to be out of range then this
 * function exits the program and prints a appropriate message.
 */
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

void showProcess(int pid)
{
    status_information information;
    if (scanStatusInformation(pid, &information) == -1)
    {
        printf("PID not found: no /proc/%d/stat virtual file was found.\n", pid);
        exit(-2);
    }
    else
    {
        printStatusInformation(information);
    }
}

void showAllProcesses() {
    int pids[1000];
    searchProcesses(pids);
    int current = 0;
    while (pids[current] != NULL)
    {
        showProcess(pids[current]);
        current++;
    }
}

int main(int argc, char **argv)
{
    showAllProcesses();
}
