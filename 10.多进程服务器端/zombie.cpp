//
// Created by starry on 19-3-16.
//

#include <stdio.h>
#include <unistd.h>

int main(int agrc, char* argv[]) {
    pid_t pid = fork();
    if(pid == 0) {
        puts("Hi, I am a child process");
    } else {
        printf("Child Process ID :%d \n", pid);
        sleep(30);
    }
    if(pid == 0)
        puts("End child process");
    else
        puts("End parent process");
    return 0;
}