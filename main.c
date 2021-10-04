#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>


/*
 * CS3305 - Assignment 2
 *
 * Created by Salman Shaikh on 2021-10-04
 * Student Number mshaik52 - 250959996
 */

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])  {
    printf(argv[1]);
    printf("\n");
    printf(argv[2]);
    printf("\n");
    printf(argv[3]);
    printf("\n");

    pid_t child_1;
    int n, status;

    child_1 = fork();

    if(child_1 > 0) {
        printf("parent (PID %d) created child_1 (PID %d).\n",getpid(),child_1);
        printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2.\n",getpid(),child_1);
    }




    return 0;
}

