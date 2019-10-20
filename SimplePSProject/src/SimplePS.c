#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main ()
{
    int i;
    int statHandle;
    char statLine[400];
	char *tokens[100];
    char *repertoryName;
    char repertoryPath[20] = "/proc/";

    struct dirent *dirp;
	DIR *dp;


	dp=opendir("/proc");
	printf("PID   -                 CMD\n");
	printf("------------------------------------\n");
	while ((dirp=readdir(dp)) != NULL){
        repertoryName = dirp->d_name;
        i=0 ;
        if (isdigit((int)repertoryName[0])){
            
            strcpy(repertoryPath, "/proc/");
            strcat(repertoryPath, dirp->d_name);
            //printf("%s", repertoryPath);      //FOR TEST PURPOSES
            
            chdir(repertoryPath);
            statHandle=open("stat",O_RDONLY);
            read(statHandle, statLine, 400);
            
            tokens[i]=strtok(statLine," ");
            while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
            
            printf("%5s - %20s\n",tokens[0],tokens[1]);
            
            close(statHandle);
        }
	}
	closedir(dp);
	exit(0);
}
