#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../procfs_reader/process.h"
#include "awesomeps_configuration.h"
#include "../procfs_reader/user_information.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256

typedef struct time
{
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
} hms_time;

const char *generalColumnNames[] = {"PID", "COMMANDE", "STATE", "TERMINAL", "USERNAME", NULL};
const char *timeColumnNames[] = {"PID", "COMMANDE", "USER TIME", "KERNEL TIME", NULL};
const char *pagingColumnNames[] = {"PID", "COMMANDE", "MINOR FAULTS", "MAJOR FAULTS", NULL};

/**
 * Converts a number of clock ticks to a number of seconds.
 */
static double clockTicksToSeconds(long unsigned clockTicks)
{
    double result = (double)clockTicks / (double)sysconf(_SC_CLK_TCK);
    return result;
}

/**
 * Extracts hours, minutes and seconds from a specified number of seconds. The
 * result is written to the given structure.
 * 
 * if time is NULL, nothing is done.
 */
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
        time.seconds);
}

static void sprintfState(char state, char *buffer)
{
    switch (state)
    {
    case 'R':
        sprintf(buffer, "Running");
        break;
    case 'S':
        sprintf(buffer, "Sleeping");
        break;
    case 'D':
        sprintf(buffer, "Waiting");
        break;
    case 'Z':
        sprintf(buffer, "Zombie");
        break;
    case 'T':
        sprintf(buffer, "Stopped");
        break;
    default:
        sprintf(buffer, "Undefined");
    }
}

/**
 * Builds a header and a separator based on an array of titles. The array
 * should be null terminated.
 * 
 * The separator is used as an interline in a table. The header is a string
 * that contains the different titles separated by '|' (column separator).
 */
static void sprintTableHeader(const char **titles, char *separator, char *header)
{
    unsigned current = 0;
    header[0] = '|';
    header[1] = 0;
    separator[0] = '+';
    separator[1] = 0;
    while (titles[current] != NULL)
    {
        sprintf(
            separator + strlen(separator),
            "%-30s+",
            "------------------------------");
        sprintf(header + strlen(header), "%-30s|", titles[current]);
        current++;
    }
}

static void sprintConfiguredTableHeader(awesomeps_configuration config,
                                        char *separator, char *header)
{
    if (config & DEFAULT_CONFIGURATION)
    {
        sprintTableHeader(generalColumnNames, separator, header);
    }    
    if (config & GENERAL_INFORMATION)
    {
        sprintTableHeader(generalColumnNames, separator, header);
    }
    if (config & PAGING_INFORMATION)
    {
        sprintTableHeader(pagingColumnNames, separator, header);
    }
    if (config & TIME_INFORMATION)
    {
        sprintTableHeader(timeColumnNames, separator, header);
    }
}

static void sprintCurrentTime(char *buffer)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(
        buffer,
        "%d-%d-%d %d:%d:%d\n",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec
    );
}

/* Prints general information about the process identified by the given pid.
 *
 * General information contain :
 *     - the process pid
 *     - the command that executed the process
 *     - the name of the owner
 */
static void printGeneralInformation(const process *info)
{
    char stateBuffer[BUFFER_SIZE];
    char userNameBuffer[BUFFER_SIZE];
    unsigned uid = getUserRealIdentifier(info->pid);
    sprintfState(info->state, stateBuffer);
    findUserName(uid, userNameBuffer);
    printf(
        "|%-30d|%-30s|%-30s|%30d|%30s|\n",
        info->pid,
        info->comm,
        stateBuffer,
        MINOR_DEVICE(info->tty_nr),
        userNameBuffer
    );
}

static void printTimeInformation(const process *info)
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
        kernelTimeBuffer);
}

/**
 * Prints information related to the paging.
 */
static void printPagingInformation(const process *info)
{
    printf(
        "|%-30d|%-30s|%-30lu|%-30lu|\n",
        info->pid,
        info->comm,
        info->minflt,
        info->majflt);
}

void showFeedback(awesomeps_configuration config)
{
    char currentTimeBuffer[BUFFER_SIZE];
    sprintCurrentTime(currentTimeBuffer);
    printf("\vCurrent time: %s\n", currentTimeBuffer);
}

void show(const process *info, awesomeps_configuration config)
{
    if (config & DEFAULT_CONFIGURATION)
    {
        printGeneralInformation(info);
    }    
    if (config & GENERAL_INFORMATION)
    {
        printGeneralInformation(info);
    }
    if (config & PAGING_INFORMATION)
    {
        printPagingInformation(info);
    }
    if (config & TIME_INFORMATION)
    {
        printTimeInformation(info);
    }
}

void showAll(const process informations[], unsigned count, awesomeps_configuration configuration)
{
    char header[BUFFER_SIZE];
    char separator[BUFFER_SIZE];
    sprintConfiguredTableHeader(configuration, separator, header);
    printf("%s\n", separator);
    printf("%s\n", header);
    printf("%s\n", separator);
    for (unsigned i = 0; i < count; i++)
    {
        show(&informations[i], configuration);
    }
    printf("%s\n", separator);
    printf("%s\n", header);
    printf("%s\n", separator);
}

void showHelp()
{
    printf("Welcome to AwesomePs!\n");
    printf("\vHere is the list of available options...\n");
    printf("\ttopic=<general | paging | time>\n");
    printf("\tpid=<pid>\n");
    printf("\tstate=<running | sleeping | waiting | zombie>\n");
    printf("\vNote: you can set multiple options at once.");
    printf(" Please refer to the README.md file to learn more about the details of this tool.\n");
}