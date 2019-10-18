#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "status_information.h"

#define PROCFS_ROOT "/proc"
#define BUFFER_SIZE 256

/* Format specifiers used to scan data from the /proc/[pid]/stat virtual file.
 * 
 * The order should not be modified as it follows the one defined in the manual
 * pages (man 5 proc, section /proc/[pid]/stat)
 */
static const char *STATUS_INFORMATION_FORMAT = "%d %s %c %d %d %d %d";

/* Reads data from the /proc/[pid]/stat file and stores it in the given
 * structure.
 */
int scanStatusInformation(int pid, status_information *information)
{
    char path[BUFFER_SIZE];
    sprintf(path, "%s/%d/stat", PROCFS_ROOT, pid);
    FILE *fp = fopen(path, "r");
    if (fp != NULL)
    {
        fscanf(fp, STATUS_INFORMATION_FORMAT,
               &(information->pid),
               information->comm,
               &(information->state),
               &(information->ppid),
               &(information->pgrp),
               &(information->session),
               &(information->tty_nr)
        );
        fclose(fp);
        return 0;
    }
    return 0;
}