#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    
    int str_len = 0;
    int idx = 0, read_len = 0;

    if(argc != 3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket()");
        exit(1);
    }

    printf("Line: %d\n", __LINE__);
    memset(&serv_addr, 0, sizeof(serv_addr));   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    printf("Line: %d\n", __LINE__);

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        perror("connect()");
        exit(1);
    }
    char message[] = "GET / HTTP/1.1";
    printf("Line: %d\n", __LINE__);
    write(sock, message, sizeof(message));
    printf("Line: %d\n", __LINE__);
    char buf[8172];
    read(sock, buf, sizeof(buf));
    printf("%s\n", buf);

    printf("Line: %d\n", __LINE__);
    int fd = open("http.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    printf("Line: %d\n", __LINE__);
    write(fd, buf, sizeof(buf));
    printf("Line: %d\n", __LINE__);
    close(fd);
    printf("Line: %d\n", __LINE__);
    close(sock);
}