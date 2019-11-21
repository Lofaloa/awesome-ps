#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../processes_filter/processes_search.h"
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
    if (strcmp(USER_KEY, opt->key) == 0)
    {
        *config |= PROCESS_BY_USER;
    }
    if (strcmp(STATE_KEY, opt->key) == 0)
    {
        *config |= PROCESS_BY_STATUS;
    }
    if (strcmp(TOPIC_KEY, opt->key) == 0)
    {
        if (strcmp(PAGING_TOPIC_VALUE, opt->value) == 0)
        {
            *config |= PAGING_INFORMATION;
        }
        if (strcmp(GENERAL_TOPIC_VALUE, opt->value) == 0)
        {
            *config |= GENERAL_INFORMATION;
        }
        if (strcmp(TIME_TOPIC_VALUE, opt->value) == 0)
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
void runWithOptions(awesomeps_option *options, unsigned count)
{
    int pids[1000];
    process informations[1000];
    unsigned current = 0;
    awesomeps_configuration configuration = EMPTY;
    configuration = getConfiguration(options, count);
    searchProcesses(pids, options, count);
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