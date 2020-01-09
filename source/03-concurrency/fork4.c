/*
 * Filename: fork4.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
    int pid, ppid;
    int i, top;
    int returnedpid;

    /* Check input arguments */
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s <value>\n", argv[0]);
        exit(1);
    }

    /* Create a new process and print */
    returnedpid = fork();
    fprintf(stdout, "fork() returned %d. My PID is %d, my parent PID is %d\n", returnedpid, (int)getpid(), (int)getppid());

    /*
    top =atoi(argv[1]);
    for (i=0; i< top;i++) {
     fprintf(stdout, "value: %d\t",i);
    }
    fprintf(stdout, "\n");
    */

    /* Wait forever */
    while (1);

    exit(0);
}
