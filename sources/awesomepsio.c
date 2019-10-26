#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include "status_information.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256
#define NULL 0

// Minor device in contained in the conbination of bits 31 and 20 and 7 to 0
#define MINOR_DEVICE(dev) ((dev)&0xff)

double clockTicksToSeconds(long unsigned clockTicks)
{
    double result =  (double) clockTicks / (double) sysconf(_SC_CLK_TCK);
    return result;
}

void printStartTime(status_information *information) {
    printf("%-15s %llu\n", "starttime", information->starttime);
}

void printTableHeader() {
    printRowSeparator();
    printf("| %-10s | %-30s | %-10s | %-10s |\n", 
        "PID",
        "Command",
        "State",
        "Terminal"
    );
    printRowSeparator();
}

void printRowSeparator() {
    printf("+%-12s+%-32s+%-12s+%-12s+\n", 
        "------------",
        "--------------------------------",
        "------------",
        "------------"
    );
}

void printStatusInformation(status_information *information)
{
    printf(
        "| %-10d | %-30s | %-10c | %10d |\n", 
        information->pid,
        information->comm,
        information->state,
        information->tty_nr
    );
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

        printf("%-15s %.2f seconds\n", "utime", clockTicksToSeconds(information->utime));
        printf("%-15s %.2f seconds\n", "stime", clockTicksToSeconds(information->stime));
        printf("%-15s %.2f seconds\n", "cutime", clockTicksToSeconds(information->cutime));
        printf("%-15s %.2f seconds\n", "cstime", clockTicksToSeconds(information->cstime));

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