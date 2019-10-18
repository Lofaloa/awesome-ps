#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "status_information_scanner.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256

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

void printTableRow(char *first, char *second, char *third) {
    
}

void printStatusInformation(status_information information) {
    printf("%-10s %-10s\n", "PID", "CMD");
    printf("%-10d %-10s\n", information.pid, information.comm);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: ps <pid>\n");
        return 1;
    }

    int pid = strtol(argv[1], NULL, 10);
    status_information information;
    scanStatusInformation(pid, &information);
    printStatusInformation(information);
    return 0;
}
