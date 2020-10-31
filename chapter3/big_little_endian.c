#include <stdio.h>
#include <sys/socket.h>

int main(void){
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host orderd port: %#x \n" , host_port);
    printf("Network oerderd port: %#x \n", net_port);
    printf("Host orderd address: %#lx \n ", host_addr);
    printf("Network orderd address: %#lx \n", net_addr);
    return 0;
}