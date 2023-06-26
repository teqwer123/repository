#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "struct.h"


#define BUF_SIZE 100
#define MAX_CLNT 256
void * gameSetting(void * arg);
void send_XY();
void error_handling(char * msg);
void * readXY(void *arg);

int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int batchCountOrder=0;

Player playerArr[13];

int main(int argc, char * argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_adr_sz;
    pthread_t t_id,read_thread;
    void * thread_return;
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutx, NULL);
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");

    while(1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt]=clnt_sock;
        pthread_mutex_unlock(&mutx);
        printf("받아온 클라이언트 소켓의 파일 디스크립터 : %d\n",clnt_socks[clnt_cnt]);

        pthread_create(&t_id, NULL, gameSetting, (void*)&clnt_sock);
        pthread_detach(t_id);
        printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
        if(clnt_cnt==13){
            break;
        }
        clnt_cnt++;
    }

    pthread_create(&read_thread,NULL, readXY, (void*)&clnt_sock);
    pthread_join(read_thread, &thread_return);
    
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
void * readXY(void *arg)
{
    int i;
    int key;
    int sock = *((int*)arg);
    while(1)
    {
        read(sock,&key, sizeof(key));
        if(key=='w'||key=='W'){
            playerArr[sock-4].xy[0]++;
        }else if(key=='s'||key=='S'){
            playerArr[sock-4].xy[0]--;
        }else if(key=='a'||key=='A'){
            playerArr[sock-4].xy[1]--;
        }else if(key=='d'||key=='D'){
            playerArr[sock-4].xy[1]++;
        }
        for(i=0; i<clnt_cnt; i++ )
        {
            write(clnt_socks[i],&playerArr,sizeof(playerArr));
        }
    }
    return NULL;
}

void *gameSetting(void * arg)
{
    
    int init_XY[13][2]={
        {4,4},{4,14},{4,24},{4,34},{14,4},{14,14},{14,24},{14,34},{24,4},{24,14},{24,24},{24,34},{34,4}
    };

    Player player;
    int key;
    int clnt_sock=*((int*)arg);
    int clnt_temp=0;
    int str_len=0, i;
    char msg[BUF_SIZE];

    pthread_mutex_lock(&mutx);
    for(i =0;i<clnt_cnt;i++)
        write(clnt_socks[i], &clnt_cnt, sizeof(clnt_cnt));
    pthread_mutex_unlock(&mutx);
    pthread_mutex_lock(&mutx);
    read(clnt_sock, &player, sizeof(player));
    player.failed=0;
    player.victory=0;
    player.xy[0] = init_XY[batchCountOrder][0];
    player.xy[1] = init_XY[batchCountOrder][1];
    playerArr[batchCountOrder]=player;
    batchCountOrder++;
    pthread_mutex_unlock(&mutx);
    pthread_mutex_lock(&mutx);
    for(i=0; i<clnt_cnt; i++)
    {
        if(clnt_sock==clnt_socks[i])
        {
            while(i++<clnt_cnt-1)
                clnt_socks[i]=clnt_socks[i+1];
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutx);

    return NULL;
}
// void send_XY()
// {
//     int i;

//     pthread_mutex_lock(&mutx);
//     for(i=0; i<clnt_cnt; i++)
//         write(clnt_socks[i], &key, sizeof(key));
//     pthread_mutex_unlock(&mutx);
// }
void error_handling(char * msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}