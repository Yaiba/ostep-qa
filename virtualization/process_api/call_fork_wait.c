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
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        //int wc = wait(NULL);
        //printf("cccccc, wc: %d\n", wc);
        //child process wait return -1
    } else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
    }
    return 0;
}
