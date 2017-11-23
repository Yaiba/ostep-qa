/*
Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?

父进程sleep一段时间可以, 不过程序中基本不可行；
TODO
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Hello yo (pid: %d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("I am child (pid: %d)\n", (int) getpid());
        printf("hello\n");
    } else {
        sleep(1);
        printf("I am parent of %d, (Pid: %d)\n", rc, (int) getpid());
        printf("goodbye\n");
    }
}
