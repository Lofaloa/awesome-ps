#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "user_interaction/awesomeps_interaction.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        runWithOptions(argc, argv);
    } if (argc == 1) {
        // TODO: show general information for processes of the current terminal
    } else {
        // TODO: show help to the user
    }
    return 0;
}
