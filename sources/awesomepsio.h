#include "status_information.h"
#include "awesomeps_formats.h"

void printTableHeader();
void printRowSeparator();
void printStatusInformation(status_information *information);
void printFullStatusInformation(status_information *information);
void printProcessInformations(status_information *info, awesomeps_format formats);