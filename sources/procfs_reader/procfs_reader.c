#include <stdio.h>

#include "process.h"
#include "user_information.h"
#include "stat_file_scanner.h"

void readProcessInformation(int pid, process *information)
{
    scanStatFile(pid, information);
}