// Used to hold the options entered by a user.
typedef struct awesomeps_option {
    char *key;
    char *value;
} awesomeps_option;

void readOptions(int argc, char **argv, awesomeps_option *options);