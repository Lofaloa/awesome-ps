#define _GNU_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>

#include "user_information.h"

#define USER_ID_KEY "Uid"
#define BUFFER_SIZE 256

long parseStringToUnsigned(char *string)
{
    char *endptr;
    long number = strtol(string, &endptr, 10);
    if (errno == ERANGE)
    {
        printf("Error while parsing %s into an unsigned.\n", string);
        exit(-1);
    }
    if (endptr == string || *endptr != '\0')
    {
        return -1;
    } else {
        return number;
    }
}

static FILE *fopenStatusFileOf(const int pid)
{
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "/proc/%d/status", pid);
    return fopen(buffer, "r");
}

static unsigned tokenizeStatusFileLine(char *line, char **tokens)
{
    unsigned count = 0;
    char *token = strtok(line, ":");
    while (token != NULL)
    {
        tokens[count] = token;
        token = strtok(NULL, "\t");
        count++;
    }
    return count;
}

int getUserRealIdentifier(const int pid)
{
    char line[BUFFER_SIZE];
    char *currentLineTokens[BUFFER_SIZE];
    FILE *status = fopenStatusFileOf(pid);
    while (fgets(line, sizeof(line), status))
    {
        tokenizeStatusFileLine(line, currentLineTokens);
        if (strcmp(currentLineTokens[0], USER_ID_KEY) == 0)
        {
            return parseStringToUnsigned(currentLineTokens[1]);
        }
    }
    fclose(status);
    return -1;
}

void findUserName(int userId, char *username)
{
    struct passwd *user = getpwuid(userId);
    if (user == NULL)
    {
        sprintf(username, "%d", userId);
    }
    else
    {
        sprintf(username, "%s", user->pw_name);
    }
}
