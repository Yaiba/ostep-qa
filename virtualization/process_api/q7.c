/*
Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?

在关闭 STDOUT 之后的输出都看不到了
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("hello, i'm %d\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("hello, i'm child (pid: %d)\n", (int) getpid());
        fclose(stdout);
        printf("hello, can U see this? (pid: %d)\n", (int) getpid());
    } else {
        printf("hello, i'm parent of %d (pid: %d)\n", rc, (int) getpid());
    }
    return 0;
}
