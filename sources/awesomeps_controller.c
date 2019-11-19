#include <string.h>

#include "awesomeps_configuration.h"
#include "interaction.h"

/**
 * Converts a given option to its related configuration flag.
 */
void setConfiguration(awesomeps_configuration *config, awesomeps_option *opt)
{
    awesomeps_configuration configuration = EMPTY;
    if (strcmp("user", opt->key) == 0) {
        configuration |= PROCESS_BY_USER;
    }
    if (strcmp("status", opt->key) == 0) {
        configuration |= PROCESS_BY_STATUS;
    }
    if (strcmp("topic", opt->key) == 0)
    {
        if (strcmp("paging", opt->value)) {
            configuration |= PAGING_INFORMATION;
        }
        if (strcmp("general", opt->value)) {
            configuration |= GENERAL_INFORMATION;
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
    parseCommandlineArguments(argc, argv, options);
    readOptions(options, argc - 1);
}