#ifndef AWESOMEPS_IO_H
#define AWESOMEPS_IO_H

#include "awesomeps_configuration.h"
#include "../procfs_reader/process.h"

// Defines the key available to the user
#define USER_KEY "user"
#define STATE_KEY "state"
#define PID_KEY "pid"
#define TOPIC_KEY "topic"

// Defines the values available for the keys
#define PAGING_TOPIC_VALUE "paging"
#define GENERAL_TOPIC_VALUE "general"
#define TIME_TOPIC_VALUE "time"
#define RUNNING_STATE_VALUE "running"
#define SLEEPING_STATE_VALUE "sleeping"
#define WAITING_STATE_VALUE "waiting"
#define ZOMBIE_STATE_VALUE "zombie"

// Defines the default option
#define DEFAULT_KEY "context" // not available for the users
#define DEFAULT_VALUE "current" // not available for the users

// Used to hold the options entered by a user.
typedef struct awesomeps_option {
    char *key;
    char *value;
} awesomeps_option;

void showFeedback();
void show(const process *, awesomeps_configuration);
void showAll(const process[], unsigned, awesomeps_configuration);
void showHelp();
unsigned parseCommandlineArguments(int argc, char **argv, awesomeps_option *options);
void runWithOptions(awesomeps_option *options, unsigned count);
void runWithConfiguration(const awesomeps_configuration configuration);

#endif /* AWESOMEPS_IO_H */