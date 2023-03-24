#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    int status;
    int pid = fork();
    // Write C code here
    if (pid == 0) { 
        int pid_child = fork();
        if (pid_child == 0) { 
            printf("I am the grandchild (%d)\n", getpid());
            exit(0);
        }
        else { 
            waitpid(pid_child, &status, 0); 
            printf("I am the child (%d)\n", getpid());
            exit(0);
        }
    }
    else {
        waitpid(pid, &status, 0); 
        printf("I am the parent (%d)\n", getpid());
    }
    return 0;
}