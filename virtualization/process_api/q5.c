/*
Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?


wait挂起调用进程直到它的其中一个子进程结束，成功会返回停止/终止的子进程的pid，否则返回-1。
wait 在子进程中调用返回 -1，如果使用errno查看会是 10 "No child processes"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        int wc = wait(0);
        printf("hello, I am child (pid:%d), wait return: %d\n", (int) getpid(), wc);
        //child process wait return -1
    } else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
    }
    return 0;
}
