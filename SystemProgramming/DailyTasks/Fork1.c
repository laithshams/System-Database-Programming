#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    pid_t child_pid;
    printf("The main process ID is %d\n",(int) getpid());
    child_pid = fork();
    printf("%d\n", child_pid);
    if(child_pid!=0){
        printf("%d\n", child_pid);
        printf("This is the parent process with id %d\n",(int) getpid() );
    }
    printf("After parent\n");
    printf("now... about the child\n");
    if(child_pid==0){
        printf("This is the child process with id %d\n",(int) getpid() );
        printf("After child %d\n",child_pid);
    }
    return 0;
}