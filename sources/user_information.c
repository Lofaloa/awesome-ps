#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


#include "user_information.h"


typedef int bool;

#define TRUE 1
#define FALSE 0

int findProcessUserId(int pid)
{
    
/** PREMIERE VERSION
    
    int userId;
    char statusFileLine[400];
    char *tokens[30];
    char filePath[30];
    int statusFileHandle;
    
    sprintf(filePath,"/proc/%d/status",pid);
    
    statusFileHandle = open(filePath,O_RDONLY);
    read(statusFileHandle, statusFileLine, 400);
    
    tokens[i]=strtok(statusFileLine," ");
    while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
            
    userId = (int)tokens[18] IS THE TOKEN WITH USER ID
            
    close(statHandle);
    
    return userId;
    
**/
    
//SECONDE VERSION
    
    int userId;
    FILE * fp;
    char * line = NULL ;
    size_t length = 0
    ssize_t read;
    char filePath[30];
    char *tokens[30];
    bool found = FALSE ;
    int i = 0;
    
    sprintf(filePath,"/proc/%d/status",pid);
    fp = fopen(filePath,"r");
    if(fp==NULL) return(-1);
    
    while((read=getline(&line, &length, fp)) -= -1 && !found)
    {
        i=0
        tokens[i]=strtok(line," ");
        while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
        if(tokens[0] == "Uid:")
        {
            found = TRUE;
            userId = tokens[1];
        }
    }
    fclose(fp);
    if(line) free(line);
    
    return userId;
}

char* findUserName(int userId)
{
    
}

