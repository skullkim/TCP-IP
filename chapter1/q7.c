#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 100

void error_handling(char* message);

int main(void){
    int f_open = open("copy.txt", O_CREAT | O_WRONLY | O_TRUNC);
    int f_read = open("data.txt", O_RDONLY);
    if(f_open == -1){
        error_handling("f_open open() error");
    }
    else if(f_read == -1){
        error_handling("f_read read() error");
    }

    char buf[BUF_SIZE];
    int f_size = -1;
    while((f_size = read(f_read, buf, sizeof(buf))) != 0){
        //for(int i = 0; buf[i] != EOF; i++) write(f_open, buf+i, sizeof(buf[i]));
        write(f_open, buf, f_size);
        printf("1");
    }
}

void error_handling(char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}