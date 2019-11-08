#include <string.h>

/**
 * Find the user id of a given process and returns it.
 * This function opens the file /proc/[pid]/status and parses it to find the user id
 * 
 * returns : -1 if fail, userId if sucessful
 */
int findProcessUserId(int pid);


/**
 * Find a user name with an user id.
 * 
 * returns : -1 if fail, userId if sucessful
 */
char* findUserName(int userId);

/**
 * Find the owner id of the executable corresponding to the pid process and returns it
 * 
 * returns : -1 if fail, userId if sucessful
 */
int findFileUserId(int pid);
