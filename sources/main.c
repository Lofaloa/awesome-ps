#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "user_interaction/awesomeps_interaction.h"
#include "procfs_reader/user_information.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        awesomeps_option options[100];
        unsigned optionsCount = parseCommandlineArguments(argc, argv, options);
        runWithOptions(options, optionsCount);
    }
    else if (argc == 1)
    {
        awesomeps_option options[100];
        options[0] = (awesomeps_option) {DEFAULT_KEY, DEFAULT_VALUE};
        options[1] = (awesomeps_option) {TOPIC_KEY, GENERAL_TOPIC_VALUE};
        runWithOptions(options, 2);
    }
    else
    {
        showHelp();
    }
    return 0;
}
