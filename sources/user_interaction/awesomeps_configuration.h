#ifndef CONFIG_H
#define CONFIG_H

/* Defines the user configurations. A configuration is used to represent a
 * combination of options.
 * 
 * For instance, if a user chooses to select processes by pid and wants to
 * print information related to paging, PROCESS_BY_PID and PAGING_INFORMATION
 * should be used, 
 */
typedef enum configuration {

   EMPTY = 0,

    /* Should be used to signal that the user wants to filter the processes by
       pid. */
    PROCESSES_BY_PID = 1 << 0,

    /* Should be used to signal that the user wants to filter the processes by
       user. */
    PROCESS_BY_USER = 1 << 1,

    /* Should be used to signal that the user wants to filter the processes by
       user. */
    PROCESS_BY_STATUS = 1 << 2,

    /* Should be used to signal that the user wants to filter the processes by
       terminal. */
    PROCESS_BY_TERMINAL = 1 << 3,

    // Should be used to print general informations about a process.
    GENERAL_INFORMATION = 1 << 4,

    // Should be used to print informations related to the process paging.
    PAGING_INFORMATION = 1 << 5,

    // Should be used to print informations related to the process time.
    TIME_INFORMATION = 1 << 6,

   DEFAULT_CONFIGURATION = 1 << 7

} awesomeps_configuration;

#endif /* CONFIG_H */