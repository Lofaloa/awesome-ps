#ifndef AWESOMEPS_IO_H
#define AWESOMEPS_IO_H

#include "awesomeps_configuration.h"
#include "../procfs_reader/process.h"

// Used to hold the options entered by a user.
typedef struct awesomeps_option {
    char *key;
    char *value;
} awesomeps_option;

void showFeedback();
void show(const process *, awesomeps_configuration);
void showAll(const process[], unsigned, awesomeps_configuration);
void parseCommandlineArguments(int argc, char **argv, awesomeps_option *options);
void runWithOptions(unsigned argc, char **argv);

#endif /* AWESOMEPS_IO_H */