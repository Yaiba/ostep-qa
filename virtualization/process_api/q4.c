/*
 Write a program that calls fork() and then calls some form of
 exec() to run the program /bin/ls. See if you can try all of the
 variants of exec(), including execl(), execle(), execlp(),
 execv(), execvp(), and execvP().

[REF: What are the different versions of exec used for in C?](https://stackoverflow.com/a/5769803/2663302)
简言之：
* 传参方式不同， L 每个参数单独传，V 参数数组
* 寻找命令方式不同，  P 会读取环境变量$PATH  没P 需要给出命令的绝对路径
* 是否修改执行命令的进程的环境，   E 可以增加额外的环境变量   没E  不增加

用exec函数可以把当前进程替换为一个新进程，且新进程与原进程有相同的PID.
shell执行命令其实就是fork了一个子进程然后用exec把子进程替换成命令执行的进程。
exec系列函数底层都是通过execve系统调用实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// different ways to pass arguments
int call_execl() {
    char *myargs[] = {"/bin/echo", "yiyayiyayo", NULL};
    printf("\nexecl----------\n");
    int rc = execl(myargs[0], myargs[0], myargs[1], myargs[2]);
    return rc;
}

int call_execv() {
    char *myargs[] = {"/bin/echo", "yiyayiyayo", NULL};
    printf("\nexecv+++++++++\n");
    int rc = execv(myargs[0], myargs);
    return rc;
}

// add extra env
// extra array of char* to the to-be-spawned process environment
int call_execle() {
    //char *myargs[] = {"./show_env.o", NULL};
    char *myargs[] = {"./show_env.o", NULL};
    //char *myargs[] = {"./show_env.sh", NULL};
    char *env[] = {"fan=5", NULL};
    printf("\nexecle----------\n");
    execle(myargs[0], myargs[0], myargs[1], env);
    return 0;
}
int call_execve() {
    //char *myargs[] = {"/bin/echo", "$fan", NULL}; not working, there is no args passing
    //下面的都是可以的，因为有明确的传递环境变量，sh脚本shell会传递，但是直接echo并没有起一个shell所以就没有传递参数，就执行失败
    // working
    //char *myargs[] = {"/usr/bin/env", NULL};
    char *myargs[] = {"./show_env.o", NULL};
    //char *myargs[] = {"./show_env.sh", NULL};
    char *env[] = {"fan=5", NULL};
    printf("\nexecve----------\n");
    execve(myargs[0], myargs, env);
    return 0;
}

// no need to specify executable path
// use $PATH search for the executable
int call_execlp() {
    char *myargs[] = {"echo", "yiyayiyayo", NULL};
    printf("\nexeclp+++++++++\n");
    int rc = execlp(myargs[0], myargs[0], myargs[1], myargs[2]);
    return rc;
}
int call_execvp() {
    char *myargs[] = {"echo", "yiyayiyayo", NULL};
    printf("\nexecvp----------\n");
    int rc = execvp(myargs[0], myargs);
    return rc;
}

int main(int argc, char *arg[])
{
    printf("hello world (pid: %d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I'm child (pid: %d)\n", (int) getpid());
        int exec_rc;
        //exec_rc = call_execl();
        //exec_rc = call_execv();
        //exec_rc = call_execlp();
        //exec_rc = call_execvp();
        //exec_rc = call_execle();
        exec_rc = call_execve();
        printf("exec return code: %d\n", exec_rc);
        printf(".........this should't print out\n");
    } else {
        wait(0);
        printf("hello, I'm parent of %d (Me pid: %d)\n", rc, (int) getpid());
    }
    return 0;
}
