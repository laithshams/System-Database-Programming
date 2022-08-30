#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
# define MAXCount 3
void ChildProcess (void);
void ParentProcess (void);
int main(){
    pid_t pid;
    pid_t pid1;
    pid = fork();
    if(pid==0)ChildProcess();
    else ParentProcess();
    pid1 = fork();
    if(pid1 == 0){
        printf("wooow");
    }
}
    void ChildProcess(void)
    {
        int i;
        for(i=0; i<=MAXCount; i++){
            printf(" This line from Child process value = %d\n", i) ;
        }
        printf(" The child process is Donnnne\n");
    }
    void ParentProcess(void)
    {
        int i;
        for(i=0; i<=MAXCount; i++){
            printf(" This line from Parent process value = %d\n", i) ;
        }
        printf(" The parent process is Donnnne\n");
    }