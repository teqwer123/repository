#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "struct.h"
#define BUF_SIZE 100
#define MAX_CLNT 256

void * gameSetting(void * arg);
void sendInfo(Player *player);
void * block_main();
void error_handling(char * msg);

int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

Player player;

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int clnt_adr_sz;

    pthread_t t_id[3];
    pthread_t block_thread;
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
        pthread_create(&t_id[clnt_cnt], NULL, gameSetting, (void*)&clnt_sock);
        pthread_detach(t_id[clnt_cnt]);
        clnt_cnt++;
        pthread_mutex_unlock(&mutx);
        printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
        if(clnt_cnt>=3){
            break;
        }
    }
    pthread_create(&block_thread,NULL,block_main, NULL);

    pthread_join(block_thread,&thread_return);
    puts("close 아직 안함");
    close(clnt_sock);
    puts("close(clnt_sock)");
    close(serv_sock);
    return 0;
}
void * block_main(){
    while(1)
    {
        sleep(1);
        if(clnt_cnt<=0)
        {
            break;
        }
    }
    return NULL;
}

void * gameSetting(void * arg)
{
    int clnt_sock=*((int*)arg);
    int i, str_len;

    while((str_len=read(clnt_sock, player.name, sizeof(player.name)))!=0)
    {
        player.fail=0;
        player.victory=0;
        player.xy[0]=0;
        player.xy[1]=0;
        sendInfo(&player);
    }


    //클라이언트가 나갈 때마다 클라이언트 수 갱신
    pthread_mutex_lock(&mutx);
    if(str_len==0){
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
    }
    pthread_mutex_unlock(&mutx);
    


    puts("return 전");
    return NULL;
}
void sendInfo(char * player)
{
    int i;
    pthread_mutex_lock(&mutx);
    for(i=0; i<clnt_cnt; i++)
        write(clnt_socks[i], &player, sizeof(player));
    pthread_mutex_unlock(&mutx);
}
void error_handling(char * msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}