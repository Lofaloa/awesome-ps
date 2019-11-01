#include <string.h>

/**
 * Find the user id of a given process and returns it.
 * This function opens the file /proc/[pid]/status and parses it to find the user id
 */
int findProcessUserId(int pid);


/**
 * Find a user name with an user id.
 */
char* findUserName(int userId);

/**
 * Find the owner id of the executable corresponding to the pid process and returns it
 */
int findFileUserId(int pid);
