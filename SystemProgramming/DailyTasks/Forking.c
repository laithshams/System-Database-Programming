#include<stdio.h> /* needed for printf() */ 
#include<unistd.h> /* needed to define fork() and getpid() */
#include<stdlib.h> /* needed to define exit */
    
int main() {
    int pid;
    switch(pid = fork())
    {
        case 0:
            printf("I am the child process, my process id is %d\n", getpid());
            break;
        default:
            printf("I am the parent process, my process id is %d\n", getpid());
                break;
        case - 1:              
            printf("error\n");             
            exit(1);
    }
}