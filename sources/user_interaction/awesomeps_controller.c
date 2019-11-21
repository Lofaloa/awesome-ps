#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../processes_filter/process_selector.h"
#include "../procfs_reader/stat_file_scanner.h"
#include "../procfs_reader/process.h"
#include "../procfs_reader/procfs_reader.h"

#include "awesomeps_configuration.h"
#include "awesomeps_interaction.h"

/**
 * Converts a given option to its related configuration flag.
 */
void setConfiguration(awesomeps_configuration *config, awesomeps_option *opt)
{
    if (strcmp("user", opt->key) == 0)
    {
        *config |= PROCESS_BY_USER;
    }
    if (strcmp("status", opt->key) == 0)
    {
        *config |= PROCESS_BY_STATUS;
    }
    if (strcmp("topic", opt->key) == 0)
    {
        if (strcmp("paging", opt->value) == 0)
        {
            *config |= PAGING_INFORMATION;
        }
        if (strcmp("general", opt->value) == 0)
        {
            *config |= GENERAL_INFORMATION;
        }
        if (strcmp("time", opt->value) == 0)
        {
            *config |= TIME_INFORMATION;
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

/**
 * Runs awesome ps with the option given by the user. If argc is equal to one
 * then the function does run anything.
 */
void runWithOptions(unsigned argc, char **argv)
{
    int pids[1000];
    process informations[1000];
    unsigned current = 0;
    awesomeps_option options[100];
    awesomeps_configuration configuration = EMPTY;
    parseCommandlineArguments(argc, argv, options);
    configuration = getConfiguration(options, argc - 1);
    searchProcesses(pids, 0, 0);
    while (pids[current] >= 0)
    {
        process information;
        readProcessInformation(pids[current], &information);
        informations[current] = information;
        current++;
    }
    showAll(informations, current, configuration);
    showFeedback();
}