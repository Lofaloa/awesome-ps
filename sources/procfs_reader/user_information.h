#include <string.h>

/**
 * Find the user id of a given process and returns it.
 * This function opens the file /proc/[pid]/status and parses it to find the user id
 * 
 * returns : -1 if fail, userId if sucessful
 */
int getUserRealIdentifier(const int pid);

/**
 * Find a user name with an user id.
 * 
 * returns : -1 if fail, user name if sucessful
 */
void findUserName(int userId, char *buffer);
