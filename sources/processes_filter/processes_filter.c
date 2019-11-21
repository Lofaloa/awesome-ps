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

static bool matchesCurrentUser(int pid)
{
    int userRealIdentifier = getUserRealIdentifier(pid);
    if (userRealIdentifier >= 0)
    {
        return getuid() == userRealIdentifier;
    }
    return false;
}

static bool matchesCurrentTerminal(int pid)
{
    process information;
    if (scanStatFile(pid, &information) == 0)
    {
        return getppid() == information.ppid || information.pid == getppid();
    }
    return false;
}

static bool matchesCurrentContext(int pid)
{
    return matchesCurrentTerminal(pid) && matchesCurrentUser(pid);
}

static bool matchesProcessIdentifier(int pid, char* pidString)
{
    int pidValue = parseProcessIdentifier(pidString);
    return pidValue >= 0 && pid == pidValue;
}

static bool matchesState(int pid, char* state)
{
    char stateChar = stateValueToCharacter(state);
    process information;
    if (scanStatFile(pid, &information) == 0)
    {
        return stateChar == information.state;
    }
    return false;
}

static bool matchesOption(int pid, const awesomeps_option *option) {
    bool matches = true;
    if (strcmp(DEFAULT_KEY, option->key) == 0)
    {
        matches &= matchesCurrentContext(pid);
    }    
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