#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main() {
    int pid;
    pid = fork();
    char *args[]={"ls","-a","/",0}; //function name, argument list,…
    char *env[]={0};
    if(pid == 0) {
        printf("about to run bin/ls\n");
        execve("/bin/ls",args,env);
        perror("execve");
    }
    if(pid > 0) {
        sleep(5);
        printf("I'm still here....");
    }
    exit(1);
}