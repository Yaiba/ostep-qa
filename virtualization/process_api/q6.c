/*
Write a slight modification of the previous program, this time using
waitpid() instead of wait(). When would waitpid() be
useful?

wait(&status) 相当于 waitpid(-1, &status, 0);
waitpid 在有多个子进程的而你想指定等待某个子进程时候有用
而且还支持 job control、不阻塞父进程(通过option参数控制)

REF: https://stackoverflow.com/a/21249082/2663302
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
    } else if (rc == 0) {
        int wc = waitpid(-1, NULL, WNOHANG);
        printf("hello, I am child (pid:%d), wait return %d\n", (int) getpid(), wc);
        //child process wait return -1
    } else {
        int wc = waitpid(rc, NULL, 0);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
    }
    return 0;
}
