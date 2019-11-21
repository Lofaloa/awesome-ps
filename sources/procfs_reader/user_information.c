#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
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
    char *lineTokens[10];
    bool found = FALSE ;
    int i = 0;
    int j = 0;
    
    sprintf(filePath,"/proc/%d/status",pid);
    fp = fopen(filePath,"r");
    if(fp==NULL) return(-1);
    
    while((read = getline(&line, &length, fp)) != -1 && !found)
    {
        i=0;
        tokens[i]=strtok(line,":");
        while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
        if(strcmp(tokens[0],"Uid")==0)
        {
            found = TRUE;
            j=0;
            lineTokens[j]=strtok(tokens[1],"\t");
            while (lineTokens[j] != NULL) lineTokens[++j]=strtok(NULL," ");
            userId = atoi(lineTokens[0]);
        }
    }
    fclose(fp);
    if(line) free(line);
    
    return userId;
}


char* findUserName(int userId)
{
    FILE * fp;
    char * line = NULL ;
    size_t length = 0;
    ssize_t read;
    char *tokens[30];
    int i = 0;
    
    fp = fopen("/etc/passwd","r");
    if(fp==NULL) return NULL;
    while((read = getline(&line, &length, fp)) != -1)
    {
        i=0;
        tokens[i]=strtok(line,":");
        while (tokens[i] != NULL) tokens[++i]=strtok(NULL,":");
        if(atoi(tokens[2]) == userId)
        {
            return tokens[0];
        }
    }
    fclose(fp);
    if(line) free(line);
    
    return NULL;
}
