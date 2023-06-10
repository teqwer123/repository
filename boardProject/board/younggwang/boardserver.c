#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "user.h"
#define MAX_LINE 105
void error_handling(char * message);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    //최대 회원 유저 수 100
    User userArr[100];


    if(argc!=2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");

    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");

    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept() error");
    //
    
    int yes;
    int joinSuccess=0;
    int read_len=0;
    int joinUserCnt = 0;
    while(yes!=3){
        read(clnt_sock, (int*)&yes, sizeof(yes));
        
        if(yes==1){
            //회원가입 로직
            User user;
            read(clnt_sock, (User*)&user,sizeof(user));  
            //받아온 유저 정보 구조체 파일에 저장
            FILE * fp = fopen("UserInfo.csv","at");
            if(fp==NULL){
                puts("파일 오픈 실패");
                return -1;
            }  
            fprintf(fp, "%s,%s,%s,%s,%s\n", user.name,user.place,user.id,user.pw,user.phoneNum);
            fclose(fp);
            joinSuccess=1;
            joinUserCnt++;//회원가입한 유저 수
            write(clnt_sock, (int*)&joinSuccess, sizeof(joinSuccess));
            
        }
        else if(yes==2){
            User user;
            int loginSuccess=0;
            char id[20];
            char pw[20];
            read(clnt_sock,(char*)&id, sizeof(id));
            read(clnt_sock,(char*)&pw, sizeof(pw));
            puts("사용자로부터 id와 pw를 받아왔습니다.");
            FILE * fp = fopen("UserInfo.csv", "rt");
            if(fp==NULL){
                puts("파일 오픈 실패");
                return -1;
            }
            int ch,i,j,commaCnt=0;
            //파일에서 한 문장(한 유저에 대한 정보) 읽어오기
            for(i = 0 ; i <joinUserCnt; i++){
                j=0;
                commaCnt=0;
                while(1){
                    //\n를 만나면 break;
                    ch=fgetc(fp);
                    if(ch=='\n'){
                        break;
                    }
                    if(ch==','){
                        commaCnt++;
                        j=0;
                    }
                    if(commaCnt==0){
                        userArr[i].name[j++]=ch;
                    }else if(commaCnt==1){
                        userArr[i].place[j++]=ch;
                    }else if(commaCnt==2){
                        userArr[i].id[j++]=ch;
                    }else if(commaCnt==3){
                        userArr[i].pw[j++]=ch;
                    }else if(commaCnt==4){
                        userArr[i].phoneNum[j++]=ch;
                    }
                }
                if(strcmp(userArr[i].id,id)==0&&strcmp(userArr[i].pw,pw)==0){
                    puts("ID와 PW가 일치합니다.");
                    loginSuccess=1;
                    write(clnt_sock, (int*)&loginSuccess, sizeof(loginSuccess));
                }
            }

            if(loginSuccess==0){
                puts("ID와 PW가 일치하지 않습니다.");
                write(clnt_sock,(int*)&loginSuccess, sizeof(loginSuccess));
            }

            fclose(fp);

        }
        else{
            //예외처리

        }
    }
    
    

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}