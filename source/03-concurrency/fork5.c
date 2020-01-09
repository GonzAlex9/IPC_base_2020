/*
 * Filename: fork5.c
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
        fprintf(stderr, "Usage: %s <value>\n", argv[0]);
        exit(1);
    }

    top = atoi(argv[1]);

    /* Create a new process and print */
    returnedpid = fork();
    fprintf(stdout, "fork() returned %d. My PID is %d, my parent PID is %d\n", returnedpid, (int)getpid(), (int)getppid());   
    
    for (i = 0; i < top; i++) {
        fprintf(stdout, "%c: value: %d\t", returnedpid ? 'P' : 'C', i);
		if (i%10 == 0) fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");

    exit(0);
}
