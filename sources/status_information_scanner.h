#include "status_information.h"

/* Reads data from the /proc/[pid]/stat file and stores it in the given
 * structure.
 */
int scanStatusInformation(int, status_information *);