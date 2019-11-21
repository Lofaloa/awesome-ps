#include <stdio.h>
#include <string.h>
#include <time.h>

#include "process_selector.h"
#include "status_information_scanner.h"
#include "awesomepsio.h"

#include "status_information.h"
#include "awesomeps_configuration.h"
#include "interaction.h"

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
    status_information informations[1000];
    unsigned current = 0;
    awesomeps_option options[100];
    awesomeps_configuration configuration = EMPTY;

    parseCommandlineArguments(argc, argv, options);
    configuration = getConfiguration(options, argc - 1);

    /* TODO: ici on peut imaginer que la fonction prenne en paramètre une
       configuration.
       Par exemple: void searchProcesses(int *, awesomeps_configuration, char *)

       Le but est de pouvoir combiner les filtres. Donc en gros il faut que si
       je donne user=logan et status=running, je ne dois avoir que les process
       dont je suis le propriétaire et qui en exécution
    */
    searchProcesses(pids, 0, 0);

    while (pids[current] >= 0)
    {
        status_information information;
        scanStatusInformation(pids[current], &information);
        informations[current] = information;
        current++;
    }
    showAll(informations, current, configuration);
    showFeedback();
}