#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "interaction.h"

#define OPTION_SEPARATOR "="

/**
 * comportement par défaut, afficher les process de l'user et tty courant (format général)
 * 
 * user = nom utilisateur
 * status = *
 * 
 * format = *
 */

/* Tells if the given key is valid. A key is value when it is an available one
 * and is not null.
 */
static int isValidKey(char *key)
{
    char *keys[] = {"user", "status", "format"};
    unsigned numberOfKeys = sizeof(keys) / sizeof(keys[0]);
    for (unsigned i = 0; i < numberOfKeys; i++) {
        if (key != NULL && strcmp(keys[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}

// Converts the given string to a valid option.
void setOptionFromString(char *str, awesomeps_option *option)
{
    char *key = strtok(str, OPTION_SEPARATOR);
    char *value = strtok(NULL, OPTION_SEPARATOR);
    if (isValidKey(key) && value != NULL) {
        option->key = key;
        option->value = value;
    } else {
        printf("Option parsing error: %s is not a valid option\n", str);
        exit(-1);
    }
}

void readOptions(int argc, char **argv, awesomeps_option *options)
{
    if (options != NULL)
    {
        for (unsigned i = 1; i < argc; i++) {
            awesomeps_option option;
            setOptionFromString(argv[i], &option);
            options[i - 1] = option;
        }
    }
}