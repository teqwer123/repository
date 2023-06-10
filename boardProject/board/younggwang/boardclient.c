#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "user.h"


void error_handling(char *message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    int str_len;

    if(argc!=3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error!");

    int yes;
    int joinSuccess=0;
    User user;
    while(yes!=3){
    //회원가입 폼 출력
    puts("1. 회원가입, 2. 로그인 3. 종료");
    scanf("%d",&yes);
    write(sock, (int*)&yes, sizeof(yes));
    if(yes==1){
        //이름, 거주지, ID, PW, 연락처
        puts("이름 : ");
        scanf("%s", user.name);
        puts("거주지 : ");
        scanf("%s",user.place);
        puts("ID : ");
        scanf("%s",user.id);
        puts("PW : ");
        scanf("%s", user.pw);
        puts("연락처 : ");
        scanf("%s",user.phoneNum);

        write(sock, (User*)&user,sizeof(user));
        read(sock, (int*)&joinSuccess, sizeof(joinSuccess));
        if(joinSuccess==1){
            puts("회원가입이 완료되었습니다.");
        }else{
            puts("회원가입에 실패했습니다.");
        }
    }
    
    //로그인 폼 출력
    else if(yes==2){
        int loginSuccess=0;
        char id[20];
        char pw[20];

        puts("ID : ");
        scanf("%s", id);
        puts("PW : ");
        scanf("%s",pw);
        puts("id,pw 입력 완료");
        write(sock, (char*)&id, sizeof(id));
        write(sock, (char*)&pw, sizeof(pw));
        read(sock,(int*)&loginSuccess, sizeof(loginSuccess));
        if(loginSuccess==1){
            puts("로그인 성공");
        }else{
            puts("로그인 실패");
        }

    }
    else{
        //예외 처리
        puts("잘못된 입력 입니다.");
    }
    }
    
    
    close(sock);
    return 0;
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}