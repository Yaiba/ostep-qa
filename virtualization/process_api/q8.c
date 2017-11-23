/*
Write a program that creates two children, and connects the standard
output of one to the standard input of the other, using the
pipe() system call.

pipe 是单向的数据流，有两个端(int fd[2] 就是两个文件描述符, 支持一般的文件描述操作)，一端接受输入(write)，一端提供输出(read)
单独一个进程建立pipe一般没什么用处，一般都会再fork一个子进程（子进程会继承/拷贝父进程的变量，文件描述符就在子进程也就能使用了），两个进程来通信(IPC)
当前进程把不使用的文件描述符close掉
fd[0] for reading, fd[1] for writing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* cmd1[] = {"echo", "left?right", NULL};
char* cmd2[] = {"tr", "a-z", "A-Z", NULL};

void setup_src(int* pfd){
    int rc = fork();
    if (rc == -1){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, i'm the src process (pid: %d)\n", getpid());
        // duplicate  stdout with pfd[1]
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[0]);
        execvp(cmd1[0], cmd1);
    } else {
        return;
    }

}

void setup_dst(int* pfd){
    int rc = fork();
    if (rc == -1){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, i'm the dst process (pid: %d)\n", getpid());
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[1]);
        execvp(cmd2[0], cmd2);
        printf("dsf process done....\n");
    } else {
        return;
    }
}

int main(int argc, char* argv[]){
    printf("hello, i'm the entry process (pid: %d)\n", getpid());
    int fd[2];
    int pid, status;

    pipe(fd);
    setup_dst(fd);
    setup_src(fd);
    close(fd[0]);
    close(fd[1]);

    while ((pid = wait(&status)) != -1)
        fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
    exit(0);
}
