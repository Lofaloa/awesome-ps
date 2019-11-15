#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>

#include "user_information.h"
#include "status_information_scanner.h"
#include "process_selector.h"

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

void searchProcesses(int *pid_array, char searchOption, char* parameter)
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
                        case 's':
                            if(matchStatus((int)pid, parameter))
                            {
                                pid_array[current] = pid;
                                current++; 
                            }
                            break;
                            
                        case 'u':
                            if(matchUser((int)pid, parameter))
                            {
                                pid_array[current] = pid;
                                current++;  
                            }
                            break;
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


bool matchCurrentUserAndTTY(int pid)
{
    bool correspondingUser = FALSE ;
    int userId = findProcessUserId(pid);
    char * currentTTY = ttyname(0);
    char * processTTY = "";
    
    if(userId == -1)
    {
        perror("Cannot find the process user id");
    }
    
    if( ( userId == (int)getuid() ) &&  (currentTTY == processTTY) )
    {
        correspondingUser = TRUE ;
    }
    
    return correspondingUser;
}

bool matchUser(int pid, char* userName)
{
    bool correspondingUser = FALSE ;
    int userId = findProcessUserId(pid);
    char* uName = findUserName(userId);
    if(userId == -1)
    {
        perror("Cannot find the process user id");
    }
    
    
    if(strcmp(uName, userName)==0)
    {
        correspondingUser = TRUE ;
    }
    
    return correspondingUser;
}


bool matchStatus(int pid, char* status)
{
    bool correspondingStatus = FALSE;
    char stateChar = status[0];
    status_information information;
    if (scanStatusInformation(pid, &information) == -1)
    {
        perror("PID not found.");
        return correspondingStatus ;
    }
    else
    {
        if(information.state == stateChar)
        {
            correspondingStatus = TRUE;
        }
    }
    return correspondingStatus;
}
