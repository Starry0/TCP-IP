//
// Created by starry on 19-3-16.
//

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig) {
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2);
}
void keycontrol(int sig) {
    if(sig == SIGINT)
        puts("CTRL+C pressed");
}

int main(int agrc, char *argv[]) {
    int i;
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);
    for(i = 0; i < 3; i ++) {
        puts("wait...");
        sleep(100); //注意实际过程中没有睡眠100s，产生信号时，为了调用信号处理器，将唤醒由于调用sleep函数而进入阻塞状态的进程。
                    //而进程一旦被唤醒，就不会再进入睡眠状态了。
    }
    return 0;
}
