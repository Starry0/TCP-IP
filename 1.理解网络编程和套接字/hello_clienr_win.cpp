//
// Created by Starry on 2019/3/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void Error_handling(char* message);

int main(int argc, char* argv[]) {
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;

    char message[30];
    int strLen;
    if(argc != 3) {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        Error_handling("WSAStartup() error!");

    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if(hSocket == INVALID_SOCKET)
        Error_handling("socket() error!");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htonl(atoi(argv[2]));

    if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        Error_handling("connect() error");

    strLen = recv(hSocket, message, sizeof(message)-1, 0);
    if(strLen == -1)
        Error_handling("read() error!");
    printf("Message from server: %s \n",message);

    closesocket(hSocket);
    WSACleanup();
    return 0;
}

void Error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}