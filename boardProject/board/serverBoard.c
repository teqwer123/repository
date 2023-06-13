#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "user2.h"
void error_handling(char *message);

void writeMemberToFile(User * user,FILE * joinFP){
    fprintf(joinFP, "%s,%s,%s,%s,%s\n",user->name,user->place,user->id,user->pw,user->phoneNum);

}

void writeBoardToFile(Board * noNameBoard, FILE * noNameBoardFP){
    fprintf(noNameBoardFP, "%s,%s,%s\n",noNameBoard->title,noNameBoard->writer,noNameBoard->content);
}

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[]="Hello World!";

    if(argc!=2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock ==-1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");

    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept() error");

    //write(clnt_sock, message, sizeof(message));
    User joinUser;
    int joinOrLogin;
    int userCount = 0;
    User loginUserFromClient;
    User loginUserFromFile;
    int loginSuccess = 0;

    int boardChoice =0;

    read(clnt_sock, &joinOrLogin, sizeof(int));
    
    switch(joinOrLogin){
        case 1:
        //회원가입
        read(clnt_sock, &joinUser, sizeof(joinUser));

        FILE * joinFP = fopen("UserInfo.csv","a");
        if(joinFP==NULL){
            printf("파일 오픈 실패\n");
            return 1;
        }
        writeMemberToFile(&joinUser,joinFP);

        //userCountFP에 회원 수 쓰기
        FILE* userCountFP = fopen("UserCount.txt","rt");
        if (userCountFP == NULL) {
            printf("Failed to open file.\n");
            return 1;
        }
        fscanf(userCountFP,"%d",&userCount);

        fclose(userCountFP);
        
        userCount++;

        userCountFP = fopen("UserCount.txt","wt");

        fprintf(userCountFP,"%d",userCount);

        fclose(userCountFP);

        fclose(joinFP);


        break;
        case 2:
        //로그인
        //클라이언트로부터 idpw 정보 수신
        read(clnt_sock,&loginUserFromClient,sizeof(loginUserFromClient));

        FILE * userInfo_FP = fopen("UserInfo.csv","rt");
        int i=0;
        while(fscanf(userInfo_FP, "%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", loginUserFromFile.name,loginUserFromFile.place,loginUserFromFile.id,loginUserFromFile.pw,loginUserFromFile.phoneNum)==5){
            if(strcmp(loginUserFromClient.id,loginUserFromFile.id)==0&&strcmp(loginUserFromClient.pw,loginUserFromFile.pw)==0){
                loginSuccess=1;
            }
        }
        //클라이언트로 로그인 성공여부 전송
        write(clnt_sock,&loginSuccess,sizeof(int));

        if(loginSuccess==1){
            //로그인 성공 시
            puts("로그인 성공");
            //클라이언트로부터 게시판 종류 선택 데이터 수신
            read(clnt_sock, &boardChoice, sizeof(boardChoice));
            switch(boardChoice){
                case 1:
                //공지사항
                break;
                case 2:
                //토론 게시판
                break;
                case 3:
                //익명 게시판

                //게시글 정보 읽어오기
                FILE * noNameBoardFP = fopen("community.csv","r");
                i =0;
                Board* noNameBoard = (Board*)malloc(sizeof(Board)*100);
                if(noNameBoard==NULL){
                    error_handling("malloc() error");
                    return -1;
                }
                while(fscanf(noNameBoardFP, "%[^,],%d,%[^,],%[^,],%[^,\n]\n", noNameBoard[i].code,&noNameBoard[i].boardNum,noNameBoard[i].title,noNameBoard[i].writer,noNameBoard[i].content)==5){
                    printf("%s,%d,%s,%s,%s\n",noNameBoard[i].code,noNameBoard[i].boardNum,noNameBoard[i].title,noNameBoard[i].writer,noNameBoard[i].content);
                    i++;
                }
                ssize_t sent_bytes=send(clnt_sock,noNameBoard,100*sizeof(Board),0);
                if(sent_bytes==-1){
                    error_handling("send() error");
                    return -1;
                }
                puts("데이터를 클라이언트로 보냈습니다.");

                //게시판 번호 or 게시글 페이지 이동 수신
                int boardNumberChoice;
                Board boardWrite;
                read(clnt_sock, &boardNumberChoice, sizeof(boardNumberChoice));

                if(boardNumberChoice!=0)
                {

                }
                else if(boardNumberChoice==0){
                    //게시글 저장
                    read(clnt_sock, &boardWrite, sizeof(boardWrite));
                    FILE * boardFP = fopen("community.csv","r");
                    Board saveBoard[100];
                    i=0;
                    while(fscanf(boardFP, "%[^,],%d,%[^,],%[^,],%[^,\n]*c", saveBoard[i].code,&saveBoard[i].boardNum,saveBoard[i].title,saveBoard[i].writer,saveBoard[i].content)==5){
                        i++;
                    }
                    
                    fclose(boardFP);

                    boardFP = fopen("community.csv","a");
                    if(boardFP==NULL){
                        puts("파일 오픈 실패");
                        return -1;
                    }
                    fprintf(boardFP,"%s,%d,%s,%s,%s\n",boardWrite.code,saveBoard[i-1].boardNum+1,boardWrite.title,boardWrite.writer,boardWrite.content);
                    fclose(boardFP);
                    puts("게시글이 저장되었습니다.");
                }

                free(noNameBoard);

                fclose(noNameBoardFP);
                

                
                break;
                case 4:
                //자유 게시판
                break;

                default:
                break;

            }

        }else{
            //로그인 실패 시
            puts("로그인 실패");
            
        }



        fclose(userInfo_FP);

        break;
        case 3:
        //종료
        break;
        default:
        break;
    }




    close(clnt_sock);
    close(serv_sock);
    return 0;
    
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}