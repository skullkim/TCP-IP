#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//void errorHandling(char *message);

void error_handlig(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;
    //IP, PORT번호 저장하는 변수
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    //소켓 생성, 생성된 소켓은 운영체제가 가지고 있다, 파일 디스크립터를 반환
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1) errorHandling("socket() error");
    //주소 정보 초기화 이전에 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    //주소정보 초기화
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    //프로그램에서 2개 이상의 소켓을 할당할 수 있다. 따라서 파일 디스크립터, 주소정보를 전달해야 한다
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }
    //파일 디스크립터를 전달해 해당 소켓을 연결해 연결요청을 받게 해야한다
    if(listen(serv_sock, 5) == -1){
        error_handling("listen() error");
    }
    clnt_addr_size = sizeof(clnt_addr);
    //요청이 있을때 까지 기다리고 연결을 했을떄  accept를 반환한다. blocking function이다
    clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1){
        error_handling("accept() error");
    }
    //메시지 전달
    write(clnt_sock, message, sizeof(message));
    //프로그램이 끝나기 전에 마지막으로 소켓을 소멸시킨다
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

