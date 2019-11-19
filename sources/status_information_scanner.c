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
 * 
 * Note: I stopped the format at stat.rsslim (25)
 */
static const char *STATUS_INFORMATION_FORMAT =
    "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld \
    %ld %llu %lu %ld %lu";

/* Scans data from the /proc/[pid]/stat file and stores it in the given
 * structure. It returns 0 on success.
 * 
 * If the specified pid does not exist in the current system state then -1 is
 * returned.
 * 
 * If the status_information pointer structure is NULL then nothing happens and
 * -1 is returned.
 * 
 * Note: I stopped the format at stat.rsslim (25)
 */
int scanStatusInformation(int pid, status_information *information)
{
    if (information != NULL)
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
                   &(information->tty_nr),
                   &(information->tpgid),
                   &(information->flags),
                   &(information->minflt),
                   &(information->cminflt),
                   &(information->majflt),
                   &(information->cmajflt),
                   &(information->utime),
                   &(information->stime),
                   &(information->cutime),
                   &(information->cstime),
                   &(information->priority),
                   &(information->nice),
                   &(information->num_threads),
                   &(information->itrealvalue),
                   &(information->starttime),
                   &(information->vsize),
                   &(information->rss),
                   &(information->rsslim));
            fclose(fp);
            return 0;
        }
    }
    return -1;
}