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
    int userId;
    FILE * fp;
    char * line = NULL ;
    size_t length = 0;
    ssize_t read;
    char filePath[30];
    char *tokens[30];
    bool found = FALSE ;
    int i = 0;
    
    sprintf(filePath,"/proc/%d/status",pid);
    fp = fopen(filePath,"r");
    if(fp==NULL) return(-1);
    
    while((read = getline(&line, &length, fp)) != -1 && !found)
    {
        i=0;
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
    char * userName;
    FILE * fp;
    char * line = NULL ;
    size_t length = 0;
    ssize_t read;
    char *tokens[30];
    bool found = FALSE ;
    int i = 0;
    
    fp = fopen("/etc/passwd","r");
    if(fp==NULL) return(-1);
    
    while((read = getline(&line, &length, fp)) != -1 && !found)
    {
        i=0;
        tokens[i]=strtok(line,":");
        while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
        if((int)tokens[2] == userId)
        {
            found = TRUE;
            userName = tokens[0];
        }
    }
    fclose(fp);
    if(line) free(line);
    
    return userName;
}


int findFileUserId(int pid)
{
    FILE * fp;
    char filePath[30];
    char * pathName;
    char * line;
    char * symbolicLink;
    size_t symbolicLinkSize;
    struct stat linkStats;
    size_t length = 0;
    ssize_t read;
    int i = 0;
    
    sprintf(filePath,"/proc/%d/exe",pid);
    
    fp = fopen(filePath,"r");
    
    while((read=getline(&line, &length, fp)) != -1)
    {
        pathName = line; 
    }
    fclose(fp);
    if(line) free(line);
    
    readlink(&pathName, &symbolicLink, &symbolicLinkSize);
    
    if(lstat(symbolicLink, &linkStats) == 0)
    {
        return (int)linkStats.st_uid;
    }else{
        return -1;
    }
}



