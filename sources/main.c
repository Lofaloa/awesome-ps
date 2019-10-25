#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

#include "status_information_scanner.h"
#include "awesomepsio.h"

int main(int argc, char **argv)
{

    status_information information;

    long pid;

    struct dirent *dirp;
    DIR *dp;
    
    int pidTable[32768];
    int i = 0;
    dp = opendir("/proc");
    printf("PID   -                 CMD\n");
    printf("------------------------------------\n");
    while ((dirp = readdir(dp)) != NULL)
    {
        if (isdigit((int)dirp->d_name))
        {

            pid = (long)dirp->d_name;

            if (scanStatusInformation(pid, &information) == -1)
            {
                printf("PID not found: no /proc/%d/stat virtual file was found.\n", pid);
                exit(-2);
            }
            else
            {
                //Here we can add some filtering criteria
                
                pidTable[i] = pid ;
                i++;
            }
        }
    }
    
    pidTable[i] = 0 ;
    
    
    closedir(dp);
    return 0;
}
