#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

#include "status_information.h"
#include "awesomeps_configuration.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256

typedef struct time {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
} hms_time;

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

/* Prints general information about the process identified by the given pid.
 *
 * General information contain :
 *     - the process pid
 *     - the command that executed the process
 *     - the name of the owner
 */
void printGeneralInformation(status_information *info)
{
    printf(
        "<pid: %-10d command: %-40s status: %-1c tty: %3d>\n",
        info->pid,
        info->comm,
        info->state,
        MINOR_DEVICE(info->tty_nr)
    );
}

void printTimeInformation(status_information *info)
{
    char userTimeBuffer[BUFFER_SIZE];
    char kernelTimeBuffer[BUFFER_SIZE];
    sprintfTime(info->utime, userTimeBuffer);
    sprintfTime(info->stime, kernelTimeBuffer);
    printf(
        "< %-10d %-40s %-15s %-15s>\n",
        info->pid,
        info->comm,
        userTimeBuffer,
        kernelTimeBuffer
    );
}

/**
 * Prints information related to the paging.
 */
void printPagingInformation(status_information *info)
{
    printf(
        "<pid: %-10d command: %-40s minor faults: %-10lu major faults: %-10lu>\n",
        info->pid,
        info->comm,
        info->minflt,
        info->majflt
    );
}

void show(status_information *info, awesomeps_configuration config)
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

void printStartTime(status_information *information)
{
    printf("%-15s %llu\n", "starttime", information->starttime);
}

/**
 * Prints all the fields of the given status information. If the structure
 * pointer is NULL then nothing happens and nothing is shown.
 * 
 * This function is meant to be used for test and demonstration purposes.
 */
void printFullStatusInformation(status_information *information)
{
    if (information != NULL)
    {
        printf("%-15s %d\n", "pid", information->pid);
        printf("%-15s %s\n", "comm", information->comm);
        printf("%-15s %c\n", "state", information->state);
        printf("%-15s %d\n", "ppid", information->ppid);
        printf("%-15s %d\n", "pgrp", information->pgrp);
        printf("%-15s %d\n", "session", information->session);
        printf("%-15s %d (minor)\n", "tty_nr", MINOR_DEVICE(information->tty_nr));
        printf("%-15s %d\n", "tpgid", information->tpgid);
        printf("%-15s %u\n", "flags", information->flags);
        printf("%-15s %lu\n", "minflt", information->minflt);
        printf("%-15s %lu\n", "cminflt", information->cminflt);
        printf("%-15s %lu\n", "majflt", information->majflt);
        printf("%-15s %lu\n", "cmajflt", information->cmajflt);

        // printf("%-15s %.2f seconds\n", "utime", clockTicksToSeconds(information->utime));
        // printf("%-15s %.2f seconds\n", "stime", clockTicksToSeconds(information->stime));
        // printf("%-15s %.2f seconds\n", "cutime", clockTicksToSeconds(information->cutime));
        // printf("%-15s %.2f seconds\n", "cstime", clockTicksToSeconds(information->cstime));

        printf("%-15s %ld\n", "priority", information->priority);
        printf("%-15s %ld\n", "nice", information->nice);
        printf("%-15s %ld\n", "num_threads", information->num_threads);
        printf("%-15s %ld\n", "itrealvalue", information->itrealvalue);

        printStartTime(information);

        printf("%-15s %lu\n", "vsize", information->vsize);
        printf("%-15s %ld\n", "rss", information->rss);
        printf("%-15s %lu\n", "rsslim", information->rsslim);
    }
}