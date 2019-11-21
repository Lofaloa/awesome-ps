#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

#include "../procfs_reader/process.h"
#include "../procfs_reader/user_information.h"
#include "../procfs_reader/stat_file_scanner.h"
#include "../user_interaction/awesomeps_configuration.h"
#include "../user_interaction/awesomeps_interaction.h"

static bool matchesCurrentUserAndTTY(int pid)
{
    bool correspondingUserAndTTY = false ;
    process information;
    int userId = findProcessUserId(pid);
    char * currentTTY = ttyname(0);
    int ttyNr = -1 ;
    
    int i = 0;
    char *tokens[30];
    
    tokens[i]=strtok(currentTTY,"/");
    while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
    if(isdigit(tokens[1][4]) != 0)
    {
        ttyNr = tokens[1][4] - '0'; //Converting char to int
    }
    
    if(userId == -1)
    {
        perror("Cannot find the process user id");
    }
    
    if (scanStatFile(pid, &information) == -1)
    {
        perror("PID not found.");
        return correspondingUserAndTTY ;
    }
    else 
    {
        if((userId == (int)getuid()) &&  (ttyNr == MINOR_DEVICE(information.tty_nr)))
        {
            correspondingUserAndTTY = true;
        }
    }
    return correspondingUserAndTTY;
}

static bool matchesUserName(int pid, char* userName)
{
    bool correspondingUser = false;
    int userId = findProcessUserId(pid);
    char* uName = findUserName(userId);
    if(userId == -1)
    {
        perror("Cannot find the process user id");
    }
    
    
    if(strcmp(uName, userName)==0)
    {
        correspondingUser = true;
    }
    
    return correspondingUser;
}


static bool matchesState(int pid, char* status)
{
    bool correspondingStatus = false;
    char stateChar = status[0];
    process information;
    if (scanStatFile(pid, &information) == -1)
    {
        perror("PID not found.");
        return correspondingStatus ;
    }
    else
    {
        if(information.state == stateChar)
        {
            correspondingStatus = true;
        }
    }
    return correspondingStatus;
}

bool matchesOptions(int pid, awesomeps_configuration config, awesomeps_option *options)
{
    return true;
}