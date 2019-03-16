//
// Created by starry on 19-3-16.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
void error_handling(const char *message);

int main(int argc, char *argv[]) {
    int sock;
    int snd_buf = 1024*3, rev_buf = 1024*3, state;
    socklen_t len;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));
    if(state)
    error_handling("getsockopt() error!");

    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rev_buf, sizeof(rev_buf));
    if(state)
        error_handling("getsockopt() error!");
    len = sizeof(snd_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
    if(state)
        error_handling("getsockopt() error!");

    len = sizeof(rev_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rev_buf, &len);
    if(state)
        error_handling("getsockopt() error!");

    printf("Input buffer size: %d \n", rev_buf);
    printf("Output buffer size: %d \n", snd_buf);
    return 0;
}
void error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}