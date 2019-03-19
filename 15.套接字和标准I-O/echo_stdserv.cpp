//
// Created by starry on 19-3-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(const char *message);


int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int str_len, i;

    socklen_t clnt_addr_sz;
    char message[BUF_SIZE];
    FILE *readfp;
    FILE *writefp;
    if(argc != 2) {
        printf("Usage: %s <port> \n",argv[0]);
        exit(1);
    }

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bin() error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_sz = sizeof(clnt_adr);

    for(i = 0; i < 5; i++) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_addr_sz);
        if(clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i+1);

        readfp = fdopen(clnt_sock, "r");
        writefp = fdopen(clnt_sock, "w");
        while (!feof(readfp)) {
            fgets(message, BUF_SIZE,readfp);
            fputs(message, writefp);
            fflush(writefp);
        }
        fclose(readfp);
        fclose(writefp);
    }
    close(serv_sock);
    return 0;
}

void error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}