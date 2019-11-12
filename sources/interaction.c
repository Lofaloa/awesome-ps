#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "interaction.h"

#define OPTION_SEPARATOR "="

// Converts the given string to a valid option.
void setOptionFromString(char *str, awesomeps_option *option)
{
    char *key = strtok(str, OPTION_SEPARATOR);
    char *value = strtok(NULL, OPTION_SEPARATOR);
    if (key != NULL && value != NULL) {
        option->key = key;
        option->value = value;
    } else {
        printf("Option parsing error: %s is not a valid option\n", str);
        exit(-1);
    }
}

void readOptions(int argc, char **argv, awesomeps_option *options)
{
    for (unsigned i = 1; i < argc; i++) {
        awesomeps_option option;
        setOptionFromString(argv[i], &option);
        options[i - 1] = option;
    }
}