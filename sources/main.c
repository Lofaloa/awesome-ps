#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "status_information_scanner.h"
#include "awesomepsio.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: ps <pid>\n");
        return 1;
    }

    int pid = strtol(argv[1], NULL, 10);
    status_information information;
    scanStatusInformation(pid, &information);
    printFullStatusInformation(&information);
    return 0;
}
