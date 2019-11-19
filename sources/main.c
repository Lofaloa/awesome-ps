#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "status_information_scanner.h"
#include "awesomeps_formats.h"
#include "process_selector.h"
#include "awesomepsio.h"
#include "user_information.h"
#include "interaction.h"

// Defines available commandline options for this tool
#define RUNTIME_OPTION "runtime"
#define PAGING_OPTION "paging"

/* Converts the given option to its corresponding format.
 *
 * If the given option is unknown or NULL, GENERAL_FORMAT is returned.
 */
awesomeps_format optionToFormat(char *option)
{
    awesomeps_format format = GENERAL_FORMAT;
    if (option != NULL)
    {
        if (strcmp(RUNTIME_OPTION, option) == 0)
        {
            format = RUNTIME_FORMAT;
        }
        else if (strcmp(PAGING_OPTION, option) == 0)
        {
            format = PAGING_FORMAT;
        }
    }
    return format;
}

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
        pid = -1;
    }
    return pid;
}

void showProcessStatusInformationFor(const int pid, awesomeps_format format)
{
    status_information information;
    if (scanStatusInformation(pid, &information) == -1)
    {
        printf("PID not found: no /proc/%d/stat virtual file was found.\n", pid);
        exit(-2);
    }
    else
    {
        printProcessInformations(&information, format);
    }
}

void printInformationsForAllProcesses(awesomeps_format format)
{
    int pids[1000];
    int current = 0;
    printTableHeader();
    while (pids[current] >= 0)
    {
        showProcessStatusInformationFor(pids[current], format);
        current++;
    }
    printRowSeparator();
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        awesomeps_option options[100];
        parseCommandlineArguments(argc, argv, options);
        readOptions(options, argc - 1);
        return 1;
    }
    return 0;
}
