#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define PROC_ROOT "/proc"

/* Parses the given directory name. If the directory name contains exclusively
 * digits is parsed and converted to a pid. 
 * 
 * If the directory name contains letters, 0 is returned.
 */
long parseProcessDirectoryName(char *dirname)
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
        return 0;
    } else {
        return pid;
    }
}

void searchProcesses(int *pid_array,enum searchOption option, char* parameter)
{
    if (pid_array != NULL) {
        struct dirent *entry;
        DIR *proc = opendir(PROC_ROOT);
        int current = 0;
        if (proc != NULL)
        {
            while ((entry = readdir(proc)) != NULL)
            {
                long pid;
                if ((pid = parseProcessDirectoryName(entry->d_name)))
                {
                    switch(searchOption)
                    {
                        case NULL:
                            pid_array[current] = pid;
                            current++;
                            break;
                            
                        case STATUS:
                            //IMPLEMENT STATUS SEARCH BASED CODE
                            break;
                            
                        case USER:
                            //IMPLEMENT USER SEARCH BASED CODE
                            
                        default:
                            pid_array[current] = pid;
                            current++;
                    }
                }
            }
            pid_array[current] = -1;
        } else {
            perror("Processes search error: ");
            exit(-1);
        }
        closedir(proc);
    }
}
