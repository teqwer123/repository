#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "user2.h"
void error_handling(char *message);

int main(int argc, char* argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
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

    // str_len=read(sock, message, sizeof(message)-1);
    // if(str_len==-1)
    //     error_handling("read() error!");
    int joinOrLogin; //회원가입인지 로그인인지 종료인지를 구분해주는 변수
    User joinUser;
    User loginUser;
    int loginSuccess = 0;
    int boardChoice = 0;
    int boardNumberChoice = 0;
    int boardContentCount = 0;

    puts("1. 회원가입 2. 로그인 3. 종료");
    scanf("%d", &joinOrLogin);
    write(sock, &joinOrLogin, sizeof(int));
    switch(joinOrLogin){
        case 1:
        //회원가입
        //이름, 거주지, ID, PW, 연락처
        puts("이름: ");
        scanf("%s",joinUser.name);
        puts("거주지: ");
        scanf("%s",joinUser.place);
        puts("ID: ");
        scanf("%s",joinUser.id);
        puts("PW: ");
        scanf("%s",joinUser.pw);
        puts("연락처: ");
        scanf("%s",joinUser.phoneNum);
        write(sock, &joinUser, sizeof(joinUser));
        break;
        case 2:
        //로그인
        puts("ID: ");
        scanf("%s",loginUser.id);
        puts("PW: ");
        scanf("%s",loginUser.pw);
        //서버로 idpw 정보 전송
        write(sock, &loginUser, sizeof(loginUser));
        //서버로부터 로그인 성공여부 수신
        read(sock,&loginSuccess, sizeof(int));
        if(loginSuccess==1){
            //로그인 성공 시
            puts("로그인 성공");
            puts("1. 공지사항 2.토론 게시판 3. 익명 게시판 4. 자유 게시판 5. ");
            scanf("%d",&boardChoice);
            //서버로 게시판 종류 선택 데이터 전송
            write(sock,&boardChoice, sizeof(boardChoice));
            switch(boardChoice){
                case 1:
                //공지사항
                break;
                case 2:
                //토론 게시판
                break;
                case 3:
                //익명 게시판
                Board* noNameBoard = (Board*)malloc(sizeof(Board)*100);
                recv(sock, noNameBoard,100*sizeof(Board),0);
                
                system("clear");
                printf("%5s %20s %20s\n","No.","title","writer");
                int boardNum=0;
                for(int i = 0 ; i < 100;i++){
                    if(strcmp(noNameBoard[i].code,"!@@###3")==0){
                        printf("%5d %20s %20s\n",boardNum+1, noNameBoard[i].title,"noname");
                        boardNum++;
                    }else{

                    }
                }
                

                puts("게시판 번호를 선택하여 게시글 페이지로 이동 or 글쓰기(0): ");
                scanf("%d",&boardNumberChoice);
                //게시판 번호or 게시글 페이지 이동 전송
                write(sock,&boardNumberChoice, sizeof(boardNumberChoice));
                system("clear");

                if(boardNumberChoice!=0){
                    int k=0;
                    while(1){
                        if(strcmp(noNameBoard[k].code,"!@@###3")==0&&noNameBoard[k].boardNum==boardNumberChoice){
                            break;
                        }
                        k++;
                    }
                    printf("|제목: %-20s\n",noNameBoard[k].title);
                    puts("----------------------------------------------");
                    printf("|작성자: %-20s\n","noname");
                    puts("----------------------------------------------");
                    printf("|%s",noNameBoard[k].content);
                    
                        
                    
                    free(noNameBoard);
                }else if(boardNumberChoice==0){
                    Board boardWrite;
                    strcpy(boardWrite.code,"!@@###3");
                    printf("%s\n",boardWrite.code);
                    while(getchar()!='\n');
                    puts("제목");
                    fgets(boardWrite.title,sizeof(boardWrite.title),stdin);
                    boardWrite.title[strcspn(boardWrite.title, "\n")] = '\0';
                    printf("%s\n",boardWrite.title);
                    // scanf("%s",boardWrite.title);
                    puts("작성자");
                    fgets(boardWrite.writer,sizeof(boardWrite.writer),stdin);
                    boardWrite.writer[strcspn(boardWrite.writer, "\n")] = '\0';
                    printf("%s\n",boardWrite.writer);
                    // scanf("%s",boardWrite.writer);
                    puts("내용");
                    fgets(boardWrite.content,sizeof(boardWrite.content),stdin);
                    boardWrite.content[strcspn(boardWrite.content, "\n")] = '\0';
                    printf("%s\n",boardWrite.content);

                    // scanf("%s",boardWrite.content);
                    write(sock, &boardWrite, sizeof(boardWrite));
                }
                

                break;
                case 4:
                //자유 게시판
                break;
                default:
                break;
                
            }
        }
        else{
            //로그인 실패 시
            puts("로그인 실패");

        }

        break;
        case 3:
        //종료
        break;
        default:
        break;
    }



    // printf("Message from server : %s \n", message);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}