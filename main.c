#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


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

    char x[100]="";
    char y[100]="";
    char z[100]="";
    strcpy(x,argv[1]);

    pid_t child_1;
    int n, status,port[2];

    //create pipe between parent and child processes
    if (pipe(port) < 0){
        perror("pipe error");
        exit(0);
    }

    child_1 = fork();

    //for parent process
    if(child_1 > 0) {
        strcpy(x,argv[1]);
        printf("parent (PID %d) created child_1 (PID %d).\n",getpid(),child_1);
        printf("parent (PID %d) receives X = \"%s\" from the user \n",getpid(),x);
        printf("parent (PID %d) writes X = \"%s\" to the pipe\n",getpid(), x);
        write(port[1],argv[1],2);
        wait(NULL);
        char fullString[100];
        read(port[0],fullString,100);
        printf("parent (PID %d) reads concatenated result from the pipe (Z =\"%s\")\n",getpid(),fullString);
    }

    //for child process
    if(child_1 == 0) {
        strcpy(y,argv[2]);
        strcpy(z,argv[3]);
        printf("child (PID %d) receives Y = \"%s\" and Z = \"%s\" from the user\n",getpid(),y,z);
        //put y and z together
        strcat(y," ");
        strcat(y,z);
        printf("child (PID %d) concatenates Y and Z to generate Y = \"%s\"\n",getpid(),y);

        char pipeRead[100];
        read(port[0],pipeRead,100);
        printf("child (PID %d) reads X from pipe = \"%s\"\n",getpid(),pipeRead);
        strcat(pipeRead," ");
        strcat(pipeRead,y);
        printf("child (PID %d) concatenates X and Y to generate Z = \"%s\"\n",getpid(),pipeRead);
        write(port[1],pipeRead,100);
        printf("child (PID %d) writes Z into the pipe\n",getpid());
    }

    return 0;
}

