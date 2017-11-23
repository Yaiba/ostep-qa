/*
Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to something
(e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?

父进程的变量，子进程会copy一份，然后两个进程对变量的操作互不影响
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("starting pid (pid:%d)\n", (int) getpid());
    int x = 0;
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("c: I am child (pid:%d)\n", (int) getpid());
        printf("c: init x = %d\n", x);
        x = 5;
        printf("c: after x = %d\n", x);
    } else {
        printf("p: I am parent (pid:%d)\n", (int) getpid());
        printf("p: init x = %d\n", x);
        x = 11;
        printf("p: after x = %d\n", x);
    }

    printf(":: x = %d\n", x);
}
