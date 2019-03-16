//
// Created by starry on 19-3-16.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 1
#define FALSE 0
void error_handling(const char *message);

int main(int argc, char *argv[]) {
    int ser_sock, clnt_sock;
    char message[30];
    int option, str_len;
    socklen_t optlen, clnt_adr_sz;
    struct sockaddr_in serv_adr, clnt_adr;
    if(argc != 2) {
        printf("Usage : %s <port> \n",argv[0]);
        exit(1);
    }
    ser_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(ser_sock == -1)
        error_handling("socket() error!");

    // 当服务器出现故障需要立即启动，由于存在Time—wait状态将需要等待几分钟，通过将SO_REUSEADDR
    // 修改为真便可将Time-wait状态下的套接字端口号重新给新的套接字。
    optlen = sizeof(option);
    option = TRUE;
    setsockopt(ser_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(ser_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)))
        error_handling("bin() error");
    if(listen(ser_sock, 5) == -1)
        error_handling("listen error");
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(ser_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

    while ((str_len = read(clnt_sock, message, sizeof(message)))!=0) {
        write(clnt_sock, message, str_len);
        write(1, message, str_len);
    }
    close(ser_sock);
    close(clnt_sock);
    return 0;
}

void error_handling(const char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}