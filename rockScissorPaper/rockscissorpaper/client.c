#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "struct.h"
#define BUF_SIZE 100
#define NAME_SIZE 20

void * sendInfo(void *arg);
void * recv_msg(void *arg);
void error_handling(char * msg);

char name[NAME_SIZE]="[DEFAULT]";
char msg[BUF_SIZE];

Player player;

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void * thread_return;
    if(argc!=4){
        printf("Usage : %s <IP> <port> <name>\n", argv[0]);
        exit(1);
    }

    sprintf(name, "[%s]", argv[3]);
    sock=socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");

    pthread_create(&snd_thread, NULL, sendInfo, (void*)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    close(sock);
    return 0;
}

void * sendInfo(void * arg)
{
    int sock=*((int*)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    
    puts("플레이어 이름 입력");
    scanf("%s",player.name);
   
    sprintf(player.name, "%s",player.name);
    write(sock, player.name, strlen(player.name));
    write(sock,NULL,0);
    
    return NULL;
}
void * recv_msg(void * arg)
{
    Player recv_player;
    int sock=*((int*)arg);
    int byteCnt;
    while(1)
    {
        byteCnt=read(sock, &recv_player, sizeof(recv_player));
        if(byteCnt==-1)
            return (void*)-1;
        // name_msg[str_len]=0;

        fputs(recv_player.name, stdout);
    }
    return NULL;
}

void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n',stderr);
    exit(1);
}