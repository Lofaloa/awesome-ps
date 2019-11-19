#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "awesomeps_controller.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        runWithOptions(argc, argv);
    }
    return 0;
}
