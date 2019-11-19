#include <stdio.h>
#include <string.h>

#include "awesomeps_configuration.h"
#include "interaction.h"

/**
 * Converts a given option to its related configuration flag.
 */
void setConfiguration(awesomeps_configuration *config, awesomeps_option *opt)
{
    if (strcmp("user", opt->key) == 0) {
        *config |= PROCESS_BY_USER;
    }
    if (strcmp("status", opt->key) == 0) {
        *config |= PROCESS_BY_STATUS;
    }
    if (strcmp("topic", opt->key) == 0)
    {
        if (strcmp("paging", opt->value) == 0) {
            *config |= PAGING_INFORMATION;
        }
        if (strcmp("general", opt->value) == 0) {
            *config |= GENERAL_INFORMATION;
        }
        if (strcmp("runtime", opt->value) == 0) {
            *config |= GENERAL_INFORMATION;
        }
    }
}

awesomeps_configuration getConfiguration(const awesomeps_option *options, unsigned count)
{
    awesomeps_configuration configuration = EMPTY;
    for (unsigned i = 0; i < count; i++)
    {
        awesomeps_option currentOption = options[i];
        setConfiguration(&configuration, &currentOption);
    }
    return configuration;
}

void runWithOptions(unsigned argc, char **argv) {
    awesomeps_option options[100];
    awesomeps_configuration configuration = EMPTY;
    parseCommandlineArguments(argc, argv, options);
    configuration = getConfiguration(options, argc - 1);

    if (configuration & PROCESS_BY_STATUS)
        printf("filter process by status\n");
    
    if (configuration & PROCESS_BY_USER)
        printf("filter process by user\n");

    if (configuration & GENERAL_INFORMATION)
        printf("show general information\n");

    if (configuration & PAGING_INFORMATION)
        printf("show paging information\n");

    if (configuration & RUNTIME_INFORMATION)
        printf("show runtime information\n");

    readOptions(options, argc - 1);
}