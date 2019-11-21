typedef int bool;

#define TRUE 1
#define FALSE 0

void searchProcesses(int *pids, char option, char* parameter);

bool matchStatus(int pid, char* status);

bool matchUser(int pid, char* userName);

bool matchCurrentUserAndTTY(int pid);

