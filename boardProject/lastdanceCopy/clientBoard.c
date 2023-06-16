#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "user2.h"
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");

    // str_len=read(sock, message, sizeof(message)-1);
    // if(str_len==-1)
    //     error_handling("read() error!");
    int joinOrLogin; // 회원가입인지 로그인인지 종료인지를 구분해주는 변수
    User joinUser;
    User loginUser;
    int loginSuccess = 0;
    int boardChoice = 0;
    int boardNumberChoice = 0;
    int boardContentCount = 0;

    puts("1. 회원가입 2. 로그인 3. 종료");
    scanf("%d", &joinOrLogin);
    write(sock, &joinOrLogin, sizeof(int));
    switch (joinOrLogin)
    {
    case 1:
        // 회원가입
        // 이름, 거주지, ID, PW, 연락처
        puts("이름: ");
        scanf("%s", joinUser.name);
        puts("거주지: ");
        scanf("%s", joinUser.place);
        puts("ID: ");
        scanf("%s", joinUser.id);
        puts("PW: ");
        scanf("%s", joinUser.pw);
        puts("연락처: ");
        scanf("%s", joinUser.phoneNum);
        write(sock, &joinUser, sizeof(joinUser));
        break;
    case 2:
        // 로그인
        puts("ID: ");
        scanf("%s", loginUser.id);
        puts("PW: ");
        scanf("%s", loginUser.pw);
        // 서버로 idpw 정보 전송
        write(sock, &loginUser, sizeof(loginUser));
        // 서버로부터 로그인 성공여부 수신
        read(sock, &loginSuccess, sizeof(int));

        if (loginSuccess == 1)
        {
            // 로그인 성공 시
            puts("로그인 성공");
            system("clear");
            puts("1. 공지사항 2.토론 게시판 3. 익명 게시판 4. 자유 게시판 ");
            scanf("%d", &boardChoice);
            // 서버로 게시판 종류 선택 데이터 전송
          

                write(sock, &boardChoice, sizeof(boardChoice));
                switch (boardChoice)
                {
                case 1:
                    // 공지사항
                    Board *noNameBoard_gong = (Board *)malloc(sizeof(Board) * 100);
                    recv(sock, noNameBoard_gong, 100 * sizeof(Board), 0);

                    system("clear");
                    printf("%5s %20s %20s\n", "No.", "제목", "글쓴이");
                    int boardNum_gong = 0;
                    for (int i = 0; i < 100; i++)
                    {
                        if (strcmp(noNameBoard_gong[i].code, "!@@###1") == 0)
                        {
                            printf("%5d %20s %20s\n", boardNum_gong + 1, noNameBoard_gong[i].title, "관리자");
                            boardNum_gong++;
                        }
                        else
                        {
                        }
                    }

                    puts("공지사항 번호를 선택하여 페이지로 이동 or 글쓰기(0) or 글삭제(444) or 글수정(333) : ");
                    scanf("%d", &boardNumberChoice);
                    // 게시판 번호or 게시글 페이지 이동 전송
                    write(sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                        int k = 0;
                        while (1)
                        {
                            if (strcmp(noNameBoard_gong[k].code, "!@@###1") == 0 && noNameBoard_gong[k].boardNum == boardNumberChoice)
                            {
                                break;
                            }
                            k++;
                        }
                        printf("|제목: %-20s\n", noNameBoard_gong[k].title);
                        puts("----------------------------------------------");
                        printf("|작성자: %-20s\n", "관리자");
                        puts("----------------------------------------------");
                        printf("|%s", noNameBoard_gong[k].content);

                        free(noNameBoard_gong);
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        puts("수정할 게시글 번호 입력:");
                        scanf("%d", &updateNum);
                        // 게시글 번호 송신
                        write(sock, &updateNum, sizeof(updateNum));
                        // 기존에 작성된 내용 보여주기

                        // 성공 시에만 가능
                        read(sock, &updateOrNot, sizeof(updateOrNot));
                        if (updateOrNot == true)
                        {

                            read(sock, &board, sizeof(board));

                            puts("기존에 작성된 게시글");
                            printf("|제목: %-20s\n", board.title);
                            puts("----------------------------------------------");
                            printf("|작성자: %-20s\n", "관리자");
                            puts("----------------------------------------------");
                            puts("|내용");
                            printf("%s\n\n", board.content);

                            // 새롭게 쓰기
                            while (getchar() != '\n')
                                ;
                            puts("제목");
                            fgets(board.title, sizeof(board.title), stdin);
                            board.title[strcspn(board.title, "\n")] = '\0';
                            printf("%s\n", board.title);
                            puts("내용");
                            fgets(board.content, sizeof(board.content), stdin);
                            board.content[strcspn(board.content, "\n")] = '\0';
                            printf("%s\n", board.content);

                            write(sock, &board, sizeof(board));
                            puts("게시글이 수정되었습니다.");
                        }

                        if (updateOrNot == false)
                        {
                            // 일치하지 않다면
                            puts("회원님이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        int deleteNum;
                        bool deleteOrNot = false;
                        puts("삭제할 글의 번호를 입력: ");
                        scanf("%d", &deleteNum);
                        write(sock, &deleteNum, sizeof(deleteNum));
                        read(sock, &deleteOrNot, sizeof(deleteOrNot));
                        if (deleteOrNot == true)
                        {
                            puts("게시글 삭제 완료");
                        }
                        else
                        {
                            puts("회원님이 작성한 게시글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 0)
                    {
                        Board boardWrite;
                        strcpy(boardWrite.code, "!@@###1");
                        printf("%s\n", boardWrite.code);
                        while (getchar() != '\n')
                            ;
                        puts("제목");
                        fgets(boardWrite.title, sizeof(boardWrite.title), stdin);
                        boardWrite.title[strcspn(boardWrite.title, "\n")] = '\0';
                        printf("%s\n", boardWrite.title);
                        // scanf("%s",boardWrite.title);
                        puts("작성자");
                        fgets(boardWrite.writer, sizeof(boardWrite.writer), stdin);
                        boardWrite.writer[strcspn(boardWrite.writer, "\n")] = '\0';
                        printf("%s\n", boardWrite.writer);
                        // scanf("%s",boardWrite.writer);
                        puts("내용");
                        fgets(boardWrite.content, sizeof(boardWrite.content), stdin);
                        boardWrite.content[strcspn(boardWrite.content, "\n")] = '\0';
                        printf("%s\n", boardWrite.content);

                        // scanf("%s",boardWrite.content);
                        write(sock, &boardWrite, sizeof(boardWrite));
                    }

                    break;
                case 2:
                    // 토론

// 서버로부터 메뉴 메시지 수신
                char buf[BUFSIZ]; // 수신한 데이터를 저장할 버퍼
                ssize_t menu_len = read(sock, buf, BUFSIZ - 1);
                if (menu_len <= 0)
                    error_handling("read() error");

                buf[menu_len] = '\0';
                printf("%s", buf);

                // 사용자로부터 옵션 선택
                int option;
                scanf("%d", &option);

                // 옵션 전송
                char option_str[2];
                sprintf(option_str, "%d", option);
                write(sock, option_str, strlen(option_str));
                if (option == 1)
                {


                    Board *noNameBo = (Board *)malloc(sizeof(Board) * 100);
                    recv(sock, noNameBo, 100 * sizeof(Board), 0);

                    system("clear");
                    printf("%5s %20s %20s\n", "No.", "제목", "글쓴이");
                    int boardN = 0;
                    for (int i = 0; i < 100; i++)
                    {
                        if (strcmp(noNameBo[i].code, "!@@###2") == 0)
                        {
                            printf("%5d %20s %20s\n", boardN + 1, noNameBo[i].title, noNameBo[i].writer);
                            boardN++;
                        }
                        else
                        {
                        }
                    }

                    puts("토론게시판 번호를 선택하여 페이지로 이동 or 글쓰기(0) or 글삭제(444) or 글수정(333) : ");
                    scanf("%d", &boardNumberChoice);
                    // 게시판 번호or 게시글 페이지 이동 전송
                    write(sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                        int k = 0;
                        while (1)
                        {
                            if (strcmp(noNameBo[k].code, "!@@###2") == 0 && noNameBo[k].boardNum == boardNumberChoice)
                            {
                                break;
                            }
                            k++;
                        }
                        printf("|제목: %-20s\n", noNameBo[k].title);
                        puts("----------------------------------------------");
                        printf("|작성자: %-20s\n", "글쓴이");
                        puts("----------------------------------------------");
                        printf("|%s", noNameBo[k].content);

                        free(noNameBo);
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        puts("수정할 게시글 번호 입력:");
                        scanf("%d", &updateNum);
                        // 게시글 번호 송신
                        write(sock, &updateNum, sizeof(updateNum));
                        // 기존에 작성된 내용 보여주기

                        // 성공 시에만 가능
                        read(sock, &updateOrNot, sizeof(updateOrNot));
                        if (updateOrNot == true)
                        {

                            read(sock, &board, sizeof(board));

                            puts("기존에 작성된 게시글");
                            printf("|제목: %-20s\n", board.title);
                            puts("----------------------------------------------");
                            printf("|작성자: %-20s\n", "글쓴이");
                            puts("----------------------------------------------");
                            puts("|내용");
                            printf("%s\n\n", board.content);

                            // 새롭게 쓰기
                            while (getchar() != '\n')
                                ;
                            puts("제목");
                            fgets(board.title, sizeof(board.title), stdin);
                            board.title[strcspn(board.title, "\n")] = '\0';
                            printf("%s\n", board.title);
                            puts("내용");
                            fgets(board.content, sizeof(board.content), stdin);
                            board.content[strcspn(board.content, "\n")] = '\0';
                            printf("%s\n", board.content);

                            write(sock, &board, sizeof(board));
                            puts("게시글이 수정되었습니다.");
                        }

                        if (updateOrNot == false)
                        {
                            // 일치하지 않다면
                            puts("회원님이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        int deleteNum;
                        bool deleteOrNot = false;
                        puts("삭제할 글의 번호를 입력: ");
                        scanf("%d", &deleteNum);
                        write(sock, &deleteNum, sizeof(deleteNum));
                        read(sock, &deleteOrNot, sizeof(deleteOrNot));
                        if (deleteOrNot == true)
                        {
                            puts("게시글 삭제 완료");
                        }
                        else
                        {
                            puts("회원님이 작성한 게시글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 0)
                    {
                        Board boardWrite;
                        strcpy(boardWrite.code, "!@@###2");
                        printf("%s\n", boardWrite.code);
                        while (getchar() != '\n')
                            ;
                        puts("제목");
                        fgets(boardWrite.title, sizeof(boardWrite.title), stdin);
                        boardWrite.title[strcspn(boardWrite.title, "\n")] = '\0';
                        printf("%s\n", boardWrite.title);
                        // scanf("%s",boardWrite.title);
                        puts("작성자");
                        fgets(boardWrite.writer, sizeof(boardWrite.writer), stdin);
                        boardWrite.writer[strcspn(boardWrite.writer, "\n")] = '\0';
                        printf("%s\n", boardWrite.writer);
                        // scanf("%s",boardWrite.writer);
                        puts("내용");
                        fgets(boardWrite.content, sizeof(boardWrite.content), stdin);
                        boardWrite.content[strcspn(boardWrite.content, "\n")] = '\0';
                        printf("%s\n", boardWrite.content);

                        // scanf("%s",boardWrite.content);
                        write(sock, &boardWrite, sizeof(boardWrite));
                    }
}
else if (option == 2)
                {


Board *noNameBo = (Board *)malloc(sizeof(Board) * 100);
                    recv(sock, noNameBo, 100 * sizeof(Board), 0);

                    system("clear");
                    printf("%5s %20s %20s\n", "No.", "제목", "글쓴이");
                    int boardN = 0;
                    for (int i = 0; i < 100; i++)
                    {
                        if (strcmp(noNameBo[i].code, "!@@###8") == 0)
                        {
                            printf("%5d %20s %20s\n", boardN + 1, noNameBo[i].title, noNameBo[i].writer);
                            boardN++;
                        }
                        else
                        {
                        }
                    }

                    puts("토론게시판 번호를 선택하여 페이지로 이동 or 글쓰기(0) or 글삭제(444) or 글수정(333) : ");
                    scanf("%d", &boardNumberChoice);
                    // 게시판 번호or 게시글 페이지 이동 전송
                    write(sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                        int k = 0;
                        while (1)
                        {
                            if (strcmp(noNameBo[k].code, "!@@###8") == 0 && noNameBo[k].boardNum == boardNumberChoice)
                            {
                                break;
                            }
                            k++;
                        }
                        printf("|제목: %-20s\n", noNameBo[k].title);
                        puts("----------------------------------------------");
                        printf("|작성자: %-20s\n", "관리자");
                        puts("----------------------------------------------");
                        printf("|%s", noNameBo[k].content);

                        free(noNameBo);
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        puts("수정할 게시글 번호 입력:");
                        scanf("%d", &updateNum);
                        // 게시글 번호 송신
                        write(sock, &updateNum, sizeof(updateNum));
                        // 기존에 작성된 내용 보여주기

                        // 성공 시에만 가능
                        read(sock, &updateOrNot, sizeof(updateOrNot));
                        if (updateOrNot == true)
                        {

                            read(sock, &board, sizeof(board));

                            puts("기존에 작성된 게시글");
                            printf("|제목: %-20s\n", board.title);
                            puts("----------------------------------------------");
                            printf("|작성자: %-20s\n", "관리자");
                            puts("----------------------------------------------");
                            puts("|내용");
                            printf("%s\n\n", board.content);

                            // 새롭게 쓰기
                            while (getchar() != '\n')
                                ;
                            puts("제목");
                            fgets(board.title, sizeof(board.title), stdin);
                            board.title[strcspn(board.title, "\n")] = '\0';
                            printf("%s\n", board.title);
                            puts("내용");
                            fgets(board.content, sizeof(board.content), stdin);
                            board.content[strcspn(board.content, "\n")] = '\0';
                            printf("%s\n", board.content);

                            write(sock, &board, sizeof(board));
                            puts("게시글이 수정되었습니다.");
                        }

                        if (updateOrNot == false)
                        {
                            // 일치하지 않다면
                            puts("회원님이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        int deleteNum;
                        bool deleteOrNot = false;
                        puts("삭제할 글의 번호를 입력: ");
                        scanf("%d", &deleteNum);
                        write(sock, &deleteNum, sizeof(deleteNum));
                        read(sock, &deleteOrNot, sizeof(deleteOrNot));
                        if (deleteOrNot == true)
                        {
                            puts("게시글 삭제 완료");
                        }
                        else
                        {
                            puts("회원님이 작성한 게시글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 0)
                    {
                        Board boardWrite;
                        strcpy(boardWrite.code, "!@@###8");
                        printf("%s\n", boardWrite.code);
                        while (getchar() != '\n')
                            ;
                        puts("제목");
                        fgets(boardWrite.title, sizeof(boardWrite.title), stdin);
                        boardWrite.title[strcspn(boardWrite.title, "\n")] = '\0';
                        printf("%s\n", boardWrite.title);
                        // scanf("%s",boardWrite.title);
                        puts("작성자");
                        fgets(boardWrite.writer, sizeof(boardWrite.writer), stdin);
                        boardWrite.writer[strcspn(boardWrite.writer, "\n")] = '\0';
                        printf("%s\n", boardWrite.writer);
                        // scanf("%s",boardWrite.writer);
                        puts("내용");
                        fgets(boardWrite.content, sizeof(boardWrite.content), stdin);
                        boardWrite.content[strcspn(boardWrite.content, "\n")] = '\0';
                        printf("%s\n", boardWrite.content);

                        // scanf("%s",boardWrite.content);
                        write(sock, &boardWrite, sizeof(boardWrite));
                    }


                }
                    break;
                case 3:
                    // 익명 게시판
                    Board *noNameBoard = (Board *)malloc(sizeof(Board) * 100);
                    recv(sock, noNameBoard, 100 * sizeof(Board), 0);

                    system("clear");
                    printf("%5s %20s %20s\n", "No.", "title", "writer");
                    int boardNum = 0;
                    for (int i = 0; i < 100; i++)
                    {
                        if (strcmp(noNameBoard[i].code, "!@@###3") == 0)
                        {
                            printf("%5d %20s %20s\n", boardNum + 1, noNameBoard[i].title, "noname");
                            boardNum++;
                        }
                        else
                        {
                        }
                    }

                    puts("게시판 번호를 선택하여 게시글 페이지로 이동 or 글쓰기(0) or 글삭제(444) or 글수정(333) : ");
                    scanf("%d", &boardNumberChoice);
                    // 게시판 번호or 게시글 페이지 이동 전송
                    write(sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                        int k = 0;
                        while (1)
                        {
                            if (strcmp(noNameBoard[k].code, "!@@###3") == 0 && noNameBoard[k].boardNum == boardNumberChoice)
                            {
                                break;
                            }
                            k++;
                        }
                        printf("|제목: %-20s\n", noNameBoard[k].title);
                        puts("----------------------------------------------");
                        printf("|작성자: %-20s\n", "noname");
                        puts("----------------------------------------------");
                        printf("|%s", noNameBoard[k].content);

                        free(noNameBoard);
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        puts("수정할 게시글 번호 입력:");
                        scanf("%d", &updateNum);
                        // 게시글 번호 송신
                        write(sock, &updateNum, sizeof(updateNum));
                        // 기존에 작성된 내용 보여주기

                        // 성공 시에만 가능
                        read(sock, &updateOrNot, sizeof(updateOrNot));
                        if (updateOrNot == true)
                        {

                            read(sock, &board, sizeof(board));

                            puts("기존에 작성된 게시글");
                            printf("|제목: %-20s\n", board.title);
                            puts("----------------------------------------------");
                            printf("|작성자: %-20s\n", "noname");
                            puts("----------------------------------------------");
                            puts("|내용");
                            printf("%s\n\n", board.content);

                            // 새롭게 쓰기
                            while (getchar() != '\n')
                                ;
                            puts("제목");
                            fgets(board.title, sizeof(board.title), stdin);
                            board.title[strcspn(board.title, "\n")] = '\0';
                            printf("%s\n", board.title);
                            puts("내용");
                            fgets(board.content, sizeof(board.content), stdin);
                            board.content[strcspn(board.content, "\n")] = '\0';
                            printf("%s\n", board.content);

                            write(sock, &board, sizeof(board));
                            puts("게시글이 수정되었습니다.");
                        }

                        if (updateOrNot == false)
                        {
                            // 일치하지 않다면
                            puts("회원님이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        int deleteNum;
                        bool deleteOrNot = false;
                        puts("삭제할 글의 번호를 입력: ");
                        scanf("%d", &deleteNum);
                        write(sock, &deleteNum, sizeof(deleteNum));
                        read(sock, &deleteOrNot, sizeof(deleteOrNot));
                        if (deleteOrNot == true)
                        {
                            puts("게시글 삭제 완료");
                        }
                        else
                        {
                            puts("회원님이 작성한 게시글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 0)
                    {
                        Board boardWrite;
                        strcpy(boardWrite.code, "!@@###3");
                        printf("%s\n", boardWrite.code);
                        while (getchar() != '\n')
                            ;
                        puts("제목");
                        fgets(boardWrite.title, sizeof(boardWrite.title), stdin);
                        boardWrite.title[strcspn(boardWrite.title, "\n")] = '\0';
                        printf("%s\n", boardWrite.title);
                        // scanf("%s",boardWrite.title);
                        puts("작성자");
                        fgets(boardWrite.writer, sizeof(boardWrite.writer), stdin);
                        boardWrite.writer[strcspn(boardWrite.writer, "\n")] = '\0';
                        printf("%s\n", boardWrite.writer);
                        // scanf("%s",boardWrite.writer);
                        puts("내용");
                        fgets(boardWrite.content, sizeof(boardWrite.content), stdin);
                        boardWrite.content[strcspn(boardWrite.content, "\n")] = '\0';
                        printf("%s\n", boardWrite.content);

                        // scanf("%s",boardWrite.content);
                        write(sock, &boardWrite, sizeof(boardWrite));
                    }

                    break;
                case 4:
                    // 자유 게시판
                    Board *freeBoard = (Board *)malloc(sizeof(Board) * 100);
                    recv(sock, freeBoard, 100 * sizeof(Board), 0);

                    system("clear");
                    printf("%5s %20s %20s\n", "No.", "title", "writer");
                    boardNum = 0;
                    for (int i = 0; i < 100; i++)
                    {
                        if (strcmp(freeBoard[i].code, "!@@###4") == 0)
                        {
                            printf("%5d %20s %20s\n", boardNum + 1, freeBoard[i].title, freeBoard[i].writer);
                            boardNum++;
                        }
                        else
                        {
                        }
                    }

                    puts("게시판 번호를 선택하여 게시글 페이지로 이동 or 글쓰기(0) or 글삭제(444) or 글수정(333): ");
                    scanf("%d", &boardNumberChoice);
                    // 게시판 번호or 게시글 페이지 이동 전송
                    write(sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                        int k = 0;
                        while (1)
                        {
                            if (strcmp(freeBoard[k].code, "!@@###4") == 0 && freeBoard[k].boardNum == boardNumberChoice)
                            {
                                break;
                            }
                            k++;
                        }
                        printf("|제목: %-20s\n", freeBoard[k].title);
                        puts("----------------------------------------------");
                        printf("|작성자: %-20s\n", "noname");
                        puts("----------------------------------------------");
                        printf("|%s", freeBoard[k].content);

                        free(freeBoard);
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        puts("수정할 게시글 번호 입력:");
                        scanf("%d", &updateNum);
                        // 게시글 번호 송신
                        write(sock, &updateNum, sizeof(updateNum));
                        // 기존에 작성된 내용 보여주기

                        // 성공 시에만 가능
                        read(sock, &updateOrNot, sizeof(updateOrNot));
                        if (updateOrNot == true)
                        {

                            read(sock, &board, sizeof(board));

                            puts("기존에 작성된 게시글");
                            printf("|제목: %-20s\n", board.title);
                            puts("----------------------------------------------");
                            printf("|작성자: %-20s\n", board.writer);
                            puts("----------------------------------------------");
                            puts("|내용");
                            printf("%s\n\n", board.content);

                            // 새롭게 쓰기
                            while (getchar() != '\n')
                                ;
                            puts("제목");
                            fgets(board.title, sizeof(board.title), stdin);
                            board.title[strcspn(board.title, "\n")] = '\0';
                            printf("%s\n", board.title);
                            puts("작성자");
                            fgets(board.writer, sizeof(board.writer), stdin);
                            board.writer[strcspn(board.writer, "\n")] = '\0';
                            printf("%s\n", board.writer);
                            puts("내용");
                            fgets(board.content, sizeof(board.content), stdin);
                            board.content[strcspn(board.content, "\n")] = '\0';
                            printf("%s\n", board.content);

                            write(sock, &board, sizeof(board));
                            puts("게시글이 수정되었습니다.");
                        }

                        if (updateOrNot == false)
                        {
                            // 일치하지 않다면
                            puts("회원님이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        int deleteNum;
                        bool deleteOrNot = false;
                        puts("삭제할 글의 번호를 입력: ");
                        scanf("%d", &deleteNum);
                        write(sock, &deleteNum, sizeof(deleteNum));
                        read(sock, &deleteOrNot, sizeof(deleteOrNot));
                        if (deleteOrNot == true)
                        {
                            puts("게시글 삭제 완료");
                        }
                        else
                        {
                            puts("회원님이 작성한 게시글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 0)
                    {
                        Board boardWrite;
                        strcpy(boardWrite.code, "!@@###4");
                        printf("%s\n", boardWrite.code);
                        while (getchar() != '\n')
                            ;
                        puts("제목");
                        fgets(boardWrite.title, sizeof(boardWrite.title), stdin);
                        boardWrite.title[strcspn(boardWrite.title, "\n")] = '\0';
                        printf("%s\n", boardWrite.title);
                        // scanf("%s",boardWrite.title);
                        puts("작성자");
                        fgets(boardWrite.writer, sizeof(boardWrite.writer), stdin);
                        boardWrite.writer[strcspn(boardWrite.writer, "\n")] = '\0';
                        printf("%s\n", boardWrite.writer);
                        // scanf("%s",boardWrite.writer);
                        puts("내용");
                        fgets(boardWrite.content, sizeof(boardWrite.content), stdin);
                        boardWrite.content[strcspn(boardWrite.content, "\n")] = '\0';
                        printf("%s\n", boardWrite.content);

                        // scanf("%s",boardWrite.content);
                        write(sock, &boardWrite, sizeof(boardWrite));
                    }
                    break;
                default:
                    break;
                }
            
        }
        else
        {
            // 로그인 실패 시
            puts("로그인 실패");
        }

        break;
    case 3:
        // 종료
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