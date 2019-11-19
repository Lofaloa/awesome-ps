#ifndef STATUS_INFORMATION_H
#define STATUS_INFORMATION_H


// Minor device in contained in the conbination of bits 31 and 20 and 7 to 0
#define MINOR_DEVICE(dev) ((dev)&0xff)

/* Holds data scanned from the /proc/[pid]/stat virtual file.
 *
 * All the fields match the data specified in the /proc/[pid]/stat section of
 * the manual page (man 5 proc).
 */
typedef struct status_information
{
    int pid;
    char comm[256];
    char state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    unsigned flags;
    long unsigned minflt;
    long unsigned cminflt;
    long unsigned majflt;
    long unsigned cmajflt;
    long unsigned utime;
    long unsigned stime;
    long int cutime;
    long int cstime;
    long int priority;
    long int nice;
    long int num_threads;
    long int itrealvalue;
    long long unsigned starttime;
    long unsigned vsize;
    long int rss;
    long unsigned rsslim;
    /* And a lot of others, some of them are marked by [PT], we should look
     * into that.
     */
} status_information;

#endif /* STATUS_INFORMATION_H */