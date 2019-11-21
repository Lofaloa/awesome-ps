#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <ctype.h>

#include "../procfs_reader/user_information.h"
#include "../procfs_reader/stat_file_scanner.h"
#include "../user_interaction/awesomeps_interaction.h"
#include "processes_filter.h"

#define PROC_ROOT "/proc"

/* Parses the given directory name. If the directory name contains exclusively
 * digits is parsed and converted to a pid. 
 * 
 * If the directory name contains letters, -1 is returned.
 */
static long parseProcessDirectoryName(char *dirname)
{
    char *endptr;
    long pid = strtol(dirname, &endptr, 10);
    if (errno == ERANGE)
    {
        printf("Directory name parsing error while parsing %s.\n", dirname);
        exit(-1);
    }
    if (endptr == dirname || *endptr != '\0')
    {
        return -1;
    } else {
        return pid;
    }
}

void searchProcesses(int *pids, const awesomeps_option *options, unsigned count)
{
    if (pids != NULL) {
        struct dirent *entry;
        DIR *proc = opendir(PROC_ROOT);
        int current = 0;
        if (proc != NULL)
        {
            while ((entry = readdir(proc)) != NULL)
            {
                long pid = parseProcessDirectoryName(entry->d_name);
                if (pid >= 0 && matchesOptions(pid, options, count))
                {
                    pids[current] = pid;
                    current++;
                }
            }
            pids[current] = -1;
        } else {
            perror("Processes search error: ");
            exit(-1);
        }
        closedir(proc);
    }
}