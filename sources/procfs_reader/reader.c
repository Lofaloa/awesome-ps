#include <stdio.h>

#include "status_information.h"
#include "user_information.h"
#include "status_information_scanner.h"

void readProcessInformationFor(int pid, status_information *information)
{
    scanStatusInformation(pid, information);
    // information->uid = findProcessUserId(pid);
    // char *userName = findUserName(information->uid);
    // sprintf(information->user_name, "%s", userName);
}