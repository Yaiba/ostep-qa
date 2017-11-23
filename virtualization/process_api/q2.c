/*
Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?

文件句柄，fork后都能使用句柄，同时 顺序不变
（在多cpu主机下； 单cpu也没有变化！！，可能是环境没模拟好吧，应该是乱序）
TODO: 模拟单cpu环境
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("starting pid (pid: %d)\n", (int) getpid());
    int rc = fork();
    FILE *wfp = fopen("/tmp/q2.txt", "a");
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("I am child (pid: %d)\n", (int) getpid());
        fprintf(wfp, "This is child fprintf writing...\n");
        fputs("This is child fputs writing...\n", wfp);
    } else {
        printf("I am parent of %d, (pid: %d)\n", rc, (int) getpid());
        fprintf(wfp, "This is parent fprintf writing...\n");
        fputs("This is parent fputs writing...\n", wfp);
    }
}
