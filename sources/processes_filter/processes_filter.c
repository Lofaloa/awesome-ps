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
#include "processes_search.h"

static char stateValueToCharacter(char * state)
{
    if (strcmp(RUNNING_STATE_VALUE, state) == 0) return 'R';
    if (strcmp(SLEEPING_STATE_VALUE, state) == 0) return 'S';
    if (strcmp(WAITING_STATE_VALUE, state) == 0) return 'D';
    if (strcmp(ZOMBIE_STATE_VALUE, state) == 0) return 'Z';
    return 0;
}

// static bool matchesCurrentUserAndTTY(int pid)
// {
//     bool correspondingUserAndTTY = false ;
//     process information;
//     int userId = findProcessUserId(pid);
//     char * currentTTY = ttyname(0);
//     int ttyNr = -1 ;
    
//     int i = 0;
//     char *tokens[30];
    
//     tokens[i]=strtok(currentTTY,"/");
//     while (tokens[i] != NULL) tokens[++i]=strtok(NULL," ");
//     if(isdigit(tokens[1][4]) != 0)
//     {
//         ttyNr = tokens[1][4] - '0'; //Converting char to int
//     }
    
//     if(userId == -1)
//     {
//         perror("Cannot find the process user id");
//     }
    
//     if (scanStatFile(pid, &information) == -1)
//     {
//         perror("PID not found.");
//         return correspondingUserAndTTY ;
//     }
//     else 
//     {
//         if((userId == (int)getuid()) &&  (ttyNr == MINOR_DEVICE(information.tty_nr)))
//         {
//             correspondingUserAndTTY = true;
//         }
//     }
//     return correspondingUserAndTTY;
// }

static bool matchesProcessIdentifier(int pid, char* pidString)
{
    int pidValue = parseProcessIdentifier(pidString);
    return pidValue >= 0 && pid == pidValue;
}

static bool matchesState(int pid, char* state)
{
    bool correspondingStatus = false;
    char stateChar = stateValueToCharacter(state);
    process information;
    if (scanStatFile(pid, &information) == 0)
    {
        return stateChar == information.state;
    }
    return correspondingStatus;
}

static bool matchesOption(int pid, const awesomeps_option *option) {
    bool matches = true;
    if (strcmp(PID_KEY, option->key) == 0)
    {
        matches &= matchesProcessIdentifier(pid, option->value);
    }
    if (strcmp(STATE_KEY, option->key) == 0)
    {
        matches &= matchesState(pid, option->value);
    }
    return matches;
}

bool matchesOptions(int pid, const awesomeps_option *options, unsigned count)
{
    unsigned current = 0;
    while (current < count && matchesOption(pid, &options[current]))
    {
        current++;
    }
    return current == count;
}