#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "status_information.h"
#include "awesomeps_configuration.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256

typedef struct time {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
} hms_time;

const char *generalColumnNames[] = {"PID", "COMMANDE", "STATE", "TERMINAL", NULL};
const char *timeColumnNames[] = {"PID", "COMMANDE", "USER TIME", "KERNEL TIME", NULL};
const char *pagingColumnNames[] = {"PID", "COMMANDE", "MINOR FAULTS", "MAJOR FAULTS", NULL};


static double clockTicksToSeconds(long unsigned clockTicks)
{
    double result =  (double) clockTicks / (double) sysconf(_SC_CLK_TCK);
    return result;
}

static void secondsToHMS(long unsigned seconds, hms_time *time)
{
    if (time != NULL)
    {
        time->hours = seconds / 3600;
        long unsigned remainder = seconds % 3600;
        time->minutes = remainder / 60;
        time->seconds = remainder % 60;
    }
}

static void sprintfTime(long unsigned clockTicks, char *buffer)
{
    hms_time time;
    secondsToHMS(clockTicksToSeconds(clockTicks), &time);
    sprintf(
        buffer,
        "%02u:%02u:%02u",
        time.hours,
        time.minutes,
        time.seconds
    );
}

/**
 * Prints the header of a table. The argument is a null terminated array
 * of strings.
 */
static void printTableHeader(const char **columnNames)
{
    unsigned current = 0;
    char buffer[256];
    char separator[256];
    buffer[0] = '|';
    separator[0] = '+';
    separator[1] = 0; // just a work around, without it random char are printed
    while (columnNames[current] != NULL)
    {
        sprintf(
            separator + strlen(separator),
            "%-30s+", 
            "------------------------------"
        );
        sprintf(buffer + strlen(buffer), "%-30s|", columnNames[current]);
        current++;
    }
    printf("%s\n", separator);
    printf("%s\n", buffer);
    printf("%s\n", separator);
}


/* Prints general information about the process identified by the given pid.
 *
 * General information contain :
 *     - the process pid
 *     - the command that executed the process
 *     - the name of the owner
 */
static void printGeneralInformation(const status_information *info)
{
    printf(
        "|%-30d|%-30s|%-30c|%30d|\n",
        info->pid,
        info->comm,
        info->state,
        MINOR_DEVICE(info->tty_nr)
    );
}

static void printTimeInformation(const status_information *info)
{
    char userTimeBuffer[BUFFER_SIZE];
    char kernelTimeBuffer[BUFFER_SIZE];
    sprintfTime(info->utime, userTimeBuffer);
    sprintfTime(info->stime, kernelTimeBuffer);
    printf(
        "|%-30d|%-30s|%-30s|%-30s|\n",
        info->pid,
        info->comm,
        userTimeBuffer,
        kernelTimeBuffer
    );
}

/**
 * Prints information related to the paging.
 */
static void printPagingInformation(const status_information *info)
{
    printf(
        "|%-30d|%-30s|%-30lu|%-30lu|\n",
        info->pid,
        info->comm,
        info->minflt,
        info->majflt
    );
}

void show(const status_information *info, awesomeps_configuration config)
{
    if (config & GENERAL_INFORMATION)
    {
        printGeneralInformation(info);
    }
    else if (config & PAGING_INFORMATION)
    {
        printPagingInformation(info);
    }
    else if (config & TIME_INFORMATION)
    {
        printTimeInformation(info);
    }
    else
    {
        printf("Display error: unkown configuration\n");
        exit(-1);
    }
}

static void printConfiguredTableHeader(awesomeps_configuration configuration)
{
    if (configuration & GENERAL_INFORMATION)
    {
        printTableHeader(generalColumnNames);
    }
    else if (configuration & PAGING_INFORMATION)
    {
        printTableHeader(pagingColumnNames);
    }
    else if (configuration & TIME_INFORMATION)
    {
        printTableHeader(timeColumnNames);
    }
    else
    {
        printf("Display error: unkown configuration\n");
        exit(-1);
    }
}

void showAll(const status_information informations[], unsigned count, awesomeps_configuration configuration)
{
    printConfiguredTableHeader(configuration);
    for (unsigned i = 0; i < count; i++)
    {
        show(&informations[i], configuration);
    }
}