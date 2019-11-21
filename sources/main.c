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
    } else {
        showHelp();
    }
    return 0;
}
