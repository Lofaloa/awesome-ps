#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "status_information.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256

/* Represents the given process state by a human readable representation.
 */
static char *stateToString(char process_state) {
    char * representation;
    switch (process_state) {
        case 'R':
            representation = "Running";
            break;
        case 'S':
            representation = "Sleeping";
            break;
        case 'Z':
            representation = "Zombie";
        default:
            representation[0] = process_state;
    }
    return representation;
}

/* Gets the complete command line for the process and sets the value in the
 * given buffer.
 *
 * Returns the size of the command line or -1 if the pid does not exist.
 */
int getProcessCommandline(int pid, char *cmdline)
{
    char path[BUFFER_SIZE];
    sprintf(path, "%s/%d/cmdline", PROCFS_ROOT, pid);
    int fd = open(path, O_RDONLY);
    if (fd > 0)
    {
        int count = read(fd, cmdline, BUFFER_SIZE);
        close(fd);
        return count;
    }
    return -1;
}

void printStatusInformation(status_information information) {
    printf("%-15s | %-15s | %-15s\n", "PID", "Command", "State");
    printf("%-15d | %-15s | %-15s\n", information.pid, information.comm, stateToString(information.state));
}

/**
 * Prints all the fields of the given status information.
 * 
 * This function is meant to be used for test and demonstration purposes.
 */
void printFullStatusInformation(status_information *information)
{
    printf("%-15s %d\n", "pid", information->pid);
    printf("%-15s %s\n", "comm", information->comm);
    printf("%-15s %c\n", "state", information->state);
    printf("%-15s %d\n", "ppid", information->ppid);
    printf("%-15s %d\n", "pgrp", information->pgrp);
    printf("%-15s %d\n", "session", information->session);
    printf("%-15s %d\n", "tty_nr", information->tty_nr);
    printf("%-15s %d\n", "tpgid", information->tpgid);
    printf("%-15s %u\n", "flags", information->flags);
    printf("%-15s %lu\n", "minflt", information->minflt);
    printf("%-15s %lu\n", "cminflt", information->cminflt);
    printf("%-15s %lu\n", "majflt", information->majflt);
    printf("%-15s %lu\n", "cmajflt", information->cmajflt);
    printf("%-15s %lu\n", "utime", information->utime);
    printf("%-15s %lu\n", "stime", information->stime);
    printf("%-15s %ld\n", "cutime", information->cutime);
    printf("%-15s %ld\n", "cstime", information->cstime);
    printf("%-15s %ld\n", "priority", information->priority);
    printf("%-15s %ld\n", "nice", information->nice);
    printf("%-15s %ld\n", "num_threads", information->num_threads);
    printf("%-15s %ld\n", "itrealvalue", information->itrealvalue);
    printf("%-15s %llu\n", "starttime", information->starttime);
    printf("%-15s %lu\n", "vsize", information->vsize);
    printf("%-15s %ld\n", "rss", information->rss);
    printf("%-15s %lu\n", "rsslim", information->rsslim);
}