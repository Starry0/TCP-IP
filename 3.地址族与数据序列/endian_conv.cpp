//
// Created by Starry on 2019/3/15.
//

#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addar = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addar);

    printf("Host ordred post:%#x \n",host_port);
    printf("Network ordred post:%#x \n",net_port);
    printf("Host ordred address:%#x \n",host_addar);
    printf("Network ordred address:%#x \n",net_addr);

    return 0;
}