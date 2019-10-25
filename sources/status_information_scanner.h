#include "status_information.h"

/* Scans data from the /proc/[pid]/stat file and stores it in the given
 * structure. It returns 0 on success.
 * 
 * If the specified pid does not exist in the current system state then -1 is
 * returned.
 * 
 * If the status_information pointer structure is NULL then nothing happens and
 * -1 is returned.
 * 
 * Note: I stopped the format at stat.rsslim (25)
 */
int scanStatusInformation(int, status_information *);

long unsigned clockTicksToSeconds(long unsigned clockTicks);