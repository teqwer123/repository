#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "user2.h"
void error_handling(char *message);

void writeMemberToFile(User *user, FILE *joinFP)
{
    fprintf(joinFP, "%s,%s,%s,%s,%s\n", user->name, user->place, user->id, user->pw, user->phoneNum);
}

void writeBoardToFile(Board *noNameBoard, FILE *noNameBoardFP)
{
    fprintf(noNameBoardFP, "%s,%s,%s\n", noNameBoard->title, noNameBoard->writer, noNameBoard->content);
}

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        error_handling("accept() error");

    // write(clnt_sock, message, sizeof(message));
    User joinUser;
    int joinOrLogin;
    int userCount = 0;
    User loginUserFromClient;
    User loginUserFromFile;
    int loginSuccess = 0;

    int boardChoice = 0;

    read(clnt_sock, &joinOrLogin, sizeof(int));

    switch (joinOrLogin)
    {
    case 1:
        // 회원가입
        read(clnt_sock, &joinUser, sizeof(joinUser));

        FILE *joinFP = fopen("UserInfo.csv", "a");
        if (joinFP == NULL)
        {
            printf("파일 오픈 실패\n");
            return 1;
        }
        writeMemberToFile(&joinUser, joinFP);

        // userCountFP에 회원 수 쓰기
        FILE *userCountFP = fopen("UserCount.txt", "rt");
        if (userCountFP == NULL)
        {
            printf("Failed to open file.\n");
            return 1;
        }
        fscanf(userCountFP, "%d", &userCount);

        fclose(userCountFP);

        userCount++;

        userCountFP = fopen("UserCount.txt", "wt");

        fprintf(userCountFP, "%d", userCount);

        fclose(userCountFP);

        fclose(joinFP);

        break;
    case 2:
        // 로그인
        // 클라이언트로부터 idpw 정보 수신
        read(clnt_sock, &loginUserFromClient, sizeof(loginUserFromClient));

        FILE *userInfo_FP = fopen("UserInfo.csv", "rt");
        int i = 0;
        while (fscanf(userInfo_FP, "%[^,],%[^,],%[^,],%[^,],%[^,\n]\n", loginUserFromFile.name, loginUserFromFile.place, loginUserFromFile.id, loginUserFromFile.pw, loginUserFromFile.phoneNum) == 5)
        {
            if (strcmp(loginUserFromClient.id, loginUserFromFile.id) == 0 && strcmp(loginUserFromClient.pw, loginUserFromFile.pw) == 0)
            {
                loginSuccess = 1;
            }
        }
        // 클라이언트로 로그인 성공여부 전송
        write(clnt_sock, &loginSuccess, sizeof(int));

        if (loginSuccess == 1)
        {
            // 로그인 성공 시
            puts("로그인 성공");
            system("clear");
            // 클라이언트로부터 게시판 종류 선택 데이터 수신
           

                read(clnt_sock, &boardChoice, sizeof(boardChoice));
                switch (boardChoice)
                {
                case 1:
                    // 공지사항

                    // 게시글 정보 읽어오기
                   
                    FILE *noNameBoardFP_gong = fopen("community.csv", "r");
                    i = 0;
                    Board *noNameBoard_gong = (Board *)malloc(sizeof(Board) * 100);
                    if (noNameBoard_gong == NULL)
                    {
                        error_handling("malloc() error");
                        return -1;
                    }
                    while (fscanf(noNameBoardFP_gong, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", noNameBoard_gong[i].code, &noNameBoard_gong[i].boardNum, noNameBoard_gong[i].id, noNameBoard_gong[i].title, noNameBoard_gong[i].writer, noNameBoard_gong[i].content) == 6)
                    {
                        printf("%s,%d,%s,%s,%s,%s\n", noNameBoard_gong[i].code, noNameBoard_gong[i].boardNum, noNameBoard_gong[i].id, noNameBoard_gong[i].title, noNameBoard_gong[i].writer, noNameBoard_gong[i].content);
                        i++;
                    }
                    ssize_t sent_bytes_gong = send(clnt_sock, noNameBoard_gong, 100 * sizeof(Board), 0);
                    if (sent_bytes_gong == -1)
                    {
                        error_handling("send() error");
                        return -1;
                    }
                    puts("데이터를 클라이언트로 보냈습니다.");

                    // 게시판 번호 or 게시글 페이지 이동 수신
                    int boardNumberChoice_gong;
                    Board boardWrite_gong;
                    Board saveBoard_gong[100];
                    read(clnt_sock, &boardNumberChoice_gong, sizeof(boardNumberChoice_gong));


                    if (boardNumberChoice_gong != 0 && boardNumberChoice_gong != 444 && boardNumberChoice_gong != 333)
                    {
                    }
                    else if (boardNumberChoice_gong == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        // 게시글 번호 수신
                        read(clnt_sock, &updateNum, sizeof(updateNum));
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_write = fopen("temp.csv", "w");
                        if (fp_read == NULL || fp_write == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_write);
                            return -1;
                        }
                        
                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", board.code, &board.boardNum, board.id, board.title, board.writer, board.content) == 6)
                        {
                            if (strcmp(board.code, "!@@###1") == 0 && strcmp(board.id, loginUserFromClient.id) == 0 && updateNum == board.boardNum)
                            {

                                updateOrNot = true;
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                                write(clnt_sock, &board, sizeof(board));
                                read(clnt_sock, &board, sizeof(board));
                            }
                            else if (strcmp(board.code, "!@@###1") == 0 && strcmp(board.id, loginUserFromClient.id) != 0 && updateNum == board.boardNum)
                            {
                                // 게시글의 작성자가 아니라면
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                            }

                            fprintf(fp_write, "%s,%d,%s,%s,%s,%s\n", board.code, board.boardNum, board.id, board.title, board.writer, board.content);
                        }

                        fclose(fp_read);
                        fclose(fp_write);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (updateOrNot == true)
                        {
                            puts("게시글이 수정되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice_gong == 444)
                    {
                        // 글 삭제
                        // 게시글 번호
                        int deleteNum;
                        Board saveBoard;
                        long location;
                        bool meetDelete = false;
                        bool deleteOrNot = false;
                        read(clnt_sock, &deleteNum, sizeof(deleteNum));

                        // 게시글 번호에 해당하는 게시글 지우기
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_delete = fopen("temp.csv", "w");
                        if (fp_delete == NULL || fp_read == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_delete);
                            return -1;
                        }
                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^\n]\n", saveBoard.code, &saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content) == 6)
                        {
                            if (strcmp(saveBoard.code, "!@@###1") == 0 && strcmp(saveBoard.id, loginUserFromClient.id) == 0 && saveBoard.boardNum == deleteNum)
                            {
                                // 익명 게시판의 글 중 사용자의 id와 일치하고 입력된 번호와 일치한 글이라면
                                meetDelete = true;
                                deleteOrNot = true;
                            }

                            if (meetDelete == false)
                            {
                                fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                            }
                            if (meetDelete == true && !(strcmp(saveBoard.code, "!@@###1") == 0 && strcmp(saveBoard.id, loginUserFromClient.id) == 0 && saveBoard.boardNum == deleteNum))
                            {
                                if (strcmp(saveBoard.code, "!@@###1") == 0)
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, deleteNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                                    deleteNum++;
                                }
                                else
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                                }
                            }
                        }

                        fclose(fp_read);
                        fclose(fp_delete);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (deleteOrNot == true)
                        {
                            puts("게시글이 삭제되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                        write(clnt_sock, &deleteOrNot, sizeof(deleteOrNot));
                    }
                    else if (boardNumberChoice_gong == 0)
                    {
                        // 게시글 저장
                        read(clnt_sock, &boardWrite_gong, sizeof(boardWrite_gong));
                        FILE *boardFP = fopen("community.csv", "r");
                        i = 0;
                        int freeLastIndex = 0;
                        while (fscanf(boardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", saveBoard_gong[i].code, &saveBoard_gong[i].boardNum, saveBoard_gong[i].id, saveBoard_gong[i].title, saveBoard_gong[i].writer, saveBoard_gong[i].content) == 6)
                        {
                            if (strcmp(saveBoard_gong[i].code, "!@@###1") == 0)
                            {
                                freeLastIndex = saveBoard_gong[i].boardNum;
                                printf("마지막 인덱스 : %d\n", freeLastIndex);
                            }
                            i++;
                        }

                        fclose(boardFP);

                        boardFP = fopen("community.csv", "a");
                        if (boardFP == NULL)
                        {
                            puts("파일 오픈 실패");
                            return -1;
                        }
                        fprintf(boardFP, "%s,%d,%s,%s,%s,%s\n", boardWrite_gong.code, freeLastIndex + 1, loginUserFromClient.id, boardWrite_gong.title, boardWrite_gong.writer, boardWrite_gong.content);
                        fclose(boardFP);
                        puts("게시글이 저장되었습니다.");
                    }

                    free(noNameBoard_gong);

                    fclose(noNameBoardFP_gong);

                    break;
                case 2:
                    // 토론 게시판
                    // 게시글 정보 읽어오기
                char buf[BUFSIZ];

                    char deb_board_msg[] = "오늘의 주제: 동성 결혼 법으로도 인정해줘야될까!👩‍❤️‍💋‍👩\n";
                write(clnt_sock, deb_board_msg, strlen(deb_board_msg));

                // 로그인 성공 시 자유 게시판 및 공지사항 목록 제공
                char menu_msg[] = "선택해주세요:\n1. 찬성 게시글 확인하기👍\n2. 반대 게시글 확인하기👎\n";
                write(clnt_sock, menu_msg, strlen(menu_msg));

                // 클라이언트로부터 선택된 옵션 수신
                ssize_t option_len = read(clnt_sock, buf, BUFSIZ - 1);
                if (option_len <= 0)
                    error_handling("read() error");

                buf[option_len] = '\0';


// 선택된 옵션에 따라 해당 내용 전송
                if (strcmp(buf, "1") == 0)
                {

                    FILE *noNameBoar = fopen("community.csv", "r");
                    i = 0;
                    Board *noNameBo = (Board *)malloc(sizeof(Board) * 100);
                    if (noNameBo == NULL)
                    {
                        error_handling("malloc() error");
                        return -1;
                    }
                    while (fscanf(noNameBoar, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", noNameBo[i].code, &noNameBo[i].boardNum, noNameBo[i].id, noNameBo[i].title, noNameBo[i].writer, noNameBo[i].content) == 6)
                    {
                        printf("%s,%d,%s,%s,%s,%s\n", noNameBo[i].code, noNameBo[i].boardNum, noNameBo[i].id, noNameBo[i].title, noNameBo[i].writer, noNameBo[i].content);
                        i++;
                    }
                    ssize_t sent_by = send(clnt_sock, noNameBo, 100 * sizeof(Board), 0);
                    if (sent_by == -1)
                    {
                        error_handling("send() error");
                        return -1;
                    }
                    puts("데이터를 클라이언트로 보냈습니다.");

                    // 게시판 번호 or 게시글 페이지 이동 수신
                    int boardNumberCho;
                    Board boardWr;
                    Board boardR;
                    Board saveBo[100];
                    read(clnt_sock, &boardNumberCho, sizeof(boardNumberCho));

                    if (boardNumberCho != 0 && boardNumberCho != 444 && boardNumberCho != 333)
                    {
                    }
                    else if (boardNumberCho == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        // 게시글 번호 수신
                        read(clnt_sock, &updateNum, sizeof(updateNum));
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_write = fopen("temp.csv", "w");
                        if (fp_read == NULL || fp_write == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_write);
                            return -1;
                        }

                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", board.code, &board.boardNum, board.id, board.title, board.writer, board.content) == 6)
                        {
                            if (strcmp(board.code, "!@@###2") == 0 && strcmp(board.id, loginUserFromClient.id) == 0 && updateNum == board.boardNum)
                            {

                                updateOrNot = true;
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                                write(clnt_sock, &board, sizeof(board));
                                read(clnt_sock, &board, sizeof(board));
                            }
                            else if (strcmp(board.code, "!@@###2") == 0 && strcmp(board.id, loginUserFromClient.id) != 0 && updateNum == board.boardNum)
                            {
                                // 게시글의 작성자가 아니라면
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                            }

                            fprintf(fp_write, "%s,%d,%s,%s,%s,%s\n", board.code, board.boardNum, board.id, board.title, board.writer, board.content);
                        }

                        fclose(fp_read);
                        fclose(fp_write);


                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (updateOrNot == true)
                        {
                            puts("게시글이 수정되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberCho == 444)
                    {
                        // 글 삭제
                        // 게시글 번호
                        int deleteNum;
                        Board saveBo;
                        long location;
                        bool meetDelete = false;
                        bool deleteOrNot = false;
                        read(clnt_sock, &deleteNum, sizeof(deleteNum));

                        // 게시글 번호에 해당하는 게시글 지우기
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_delete = fopen("temp.csv", "w");
                        if (fp_delete == NULL || fp_read == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_delete);
                            return -1;
                        }
                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^\n]\n", saveBo.code, &saveBo.boardNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content) == 6)
                        {
                            if (strcmp(saveBo.code, "!@@###2") == 0 && strcmp(saveBo.id, loginUserFromClient.id) == 0 && saveBo.boardNum == deleteNum)
                            {
                                // 익명 게시판의 글 중 사용자의 id와 일치하고 입력된 번호와 일치한 글이라면
                                meetDelete = true;
                                deleteOrNot = true;
                            }

                            if (meetDelete == false)
                            {
                                fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBo.code, saveBo.boardNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content);
                            }
                            if (meetDelete == true && !(strcmp(saveBo.code, "!@@###2") == 0 && strcmp(saveBo.id, loginUserFromClient.id) == 0 && saveBo.boardNum == deleteNum))
                            {
                                if (strcmp(saveBo.code, "!@@###2") == 0)
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBo.code, deleteNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content);
                                    deleteNum++;
                                }
                                else
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBo.code, saveBo.boardNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content);
                                }
                            }
                        }

                        fclose(fp_read);
                        fclose(fp_delete);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (deleteOrNot == true)
                        {
                            puts("게시글이 삭제되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                        write(clnt_sock, &deleteOrNot, sizeof(deleteOrNot));
                    }
                    else if (boardNumberCho == 0)
                    {
                        // 게시글 저장
                        read(clnt_sock, &boardWr, sizeof(boardWr));
                        FILE *boardFP = fopen("community.csv", "r");
                        i = 0;
                        int freeLastIndex = 0;
                        while (fscanf(boardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", saveBo[i].code, &saveBo[i].boardNum, saveBo[i].id, saveBo[i].title, saveBo[i].writer, saveBo[i].content) == 6)
                        {
                            if (strcmp(saveBo[i].code, "!@@###2") == 0)
                            {
                                freeLastIndex = saveBo[i].boardNum;
                                printf("마지막 인덱스 : %d\n", freeLastIndex);
                            }
                            i++;
                        }

                        fclose(boardFP);

                        boardFP = fopen("community.csv", "a");
                        if (boardFP == NULL)
                        {
                            puts("파일 오픈 실패");
                            return -1;
                        }
                        fprintf(boardFP, "%s,%d,%s,%s,%s,%s\n", boardWr.code, freeLastIndex + 1, loginUserFromClient.id, boardWr.title, boardWr.writer, boardWr.content);
                        fclose(boardFP);
                        puts("게시글이 저장되었습니다.");
                    }

                    free(noNameBo);

                    fclose(noNameBoar);

                }
                else if (strcmp(buf, "2") == 0)
                {

                     FILE *noNameBoar = fopen("community.csv", "r");
                    i = 0;
                    Board *noNameBo = (Board *)malloc(sizeof(Board) * 100);
                    if (noNameBo == NULL)
                    {
                        error_handling("malloc() error");
                        return -1;
                    }
                    while (fscanf(noNameBoar, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", noNameBo[i].code, &noNameBo[i].boardNum, noNameBo[i].id, noNameBo[i].title, noNameBo[i].writer, noNameBo[i].content) == 6)
                    {
                        printf("%s,%d,%s,%s,%s,%s\n", noNameBo[i].code, noNameBo[i].boardNum, noNameBo[i].id, noNameBo[i].title, noNameBo[i].writer, noNameBo[i].content);
                        i++;
                    }
                    ssize_t sent_by = send(clnt_sock, noNameBo, 100 * sizeof(Board), 0);
                    if (sent_by == -1)
                    {
                        error_handling("send() error");
                        return -1;
                    }
                    puts("데이터를 클라이언트로 보냈습니다.");

                    // 게시판 번호 or 게시글 페이지 이동 수신
                    int boardNumberCho;
                    Board boardWr;
                    Board boardR;
                    Board saveBo[100];
                    read(clnt_sock, &boardNumberCho, sizeof(boardNumberCho));

                    if (boardNumberCho != 0 && boardNumberCho != 444 && boardNumberCho != 333)
                    {
                    }
                    else if (boardNumberCho == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        // 게시글 번호 수신
                        read(clnt_sock, &updateNum, sizeof(updateNum));
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_write = fopen("temp.csv", "w");
                        if (fp_read == NULL || fp_write == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_write);
                            return -1;
                        }

                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", board.code, &board.boardNum, board.id, board.title, board.writer, board.content) == 6)
                        {
                            if (strcmp(board.code, "!@@###8") == 0 && strcmp(board.id, loginUserFromClient.id) == 0 && updateNum == board.boardNum)
                            {

                                updateOrNot = true;
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                                write(clnt_sock, &board, sizeof(board));
                                read(clnt_sock, &board, sizeof(board));
                            }
                            else if (strcmp(board.code, "!@@###8") == 0 && strcmp(board.id, loginUserFromClient.id) != 0 && updateNum == board.boardNum)
                            {
                                // 게시글의 작성자가 아니라면
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                            }

                            fprintf(fp_write, "%s,%d,%s,%s,%s,%s\n", board.code, board.boardNum, board.id, board.title, board.writer, board.content);
                        }

                        fclose(fp_read);
                        fclose(fp_write);


                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (updateOrNot == true)
                        {
                            puts("게시글이 수정되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberCho == 444)
                    {
                        // 글 삭제
                        // 게시글 번호
                        int deleteNum;
                        Board saveBo;
                        long location;
                        bool meetDelete = false;
                        bool deleteOrNot = false;
                        read(clnt_sock, &deleteNum, sizeof(deleteNum));

                        // 게시글 번호에 해당하는 게시글 지우기
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_delete = fopen("temp.csv", "w");
                        if (fp_delete == NULL || fp_read == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_delete);
                            return -1;
                        }
                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^\n]\n", saveBo.code, &saveBo.boardNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content) == 6)
                        {
                            if (strcmp(saveBo.code, "!@@###8") == 0 && strcmp(saveBo.id, loginUserFromClient.id) == 0 && saveBo.boardNum == deleteNum)
                            {
                                // 익명 게시판의 글 중 사용자의 id와 일치하고 입력된 번호와 일치한 글이라면
                                meetDelete = true;
                                deleteOrNot = true;
                            }

                            if (meetDelete == false)
                            {
                                fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBo.code, saveBo.boardNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content);
                            }
                            if (meetDelete == true && !(strcmp(saveBo.code, "!@@###8") == 0 && strcmp(saveBo.id, loginUserFromClient.id) == 0 && saveBo.boardNum == deleteNum))
                            {
                                if (strcmp(saveBo.code, "!@@###8") == 0)
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBo.code, deleteNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content);
                                    deleteNum++;
                                }
                                else
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBo.code, saveBo.boardNum, saveBo.id, saveBo.title, saveBo.writer, saveBo.content);
                                }
                            }
                        }

                        fclose(fp_read);
                        fclose(fp_delete);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (deleteOrNot == true)
                        {
                            puts("게시글이 삭제되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                        write(clnt_sock, &deleteOrNot, sizeof(deleteOrNot));
                    }
                    else if (boardNumberCho == 0)
                    {
                        // 게시글 저장
                        read(clnt_sock, &boardWr, sizeof(boardWr));
                        FILE *boardFP = fopen("community.csv", "r");
                        i = 0;
                        int freeLastIndex = 0;
                        while (fscanf(boardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", saveBo[i].code, &saveBo[i].boardNum, saveBo[i].id, saveBo[i].title, saveBo[i].writer, saveBo[i].content) == 6)
                        {
                            if (strcmp(saveBo[i].code, "!@@###8") == 0)
                            {
                                freeLastIndex = saveBo[i].boardNum;
                                printf("마지막 인덱스 : %d\n", freeLastIndex);
                            }
                            i++;
                        }

                        fclose(boardFP);

                        boardFP = fopen("community.csv", "a");
                        if (boardFP == NULL)
                        {
                            puts("파일 오픈 실패");
                            return -1;
                        }
                        fprintf(boardFP, "%s,%d,%s,%s,%s,%s\n", boardWr.code, freeLastIndex + 1, loginUserFromClient.id, boardWr.title, boardWr.writer, boardWr.content);
                        fclose(boardFP);
                        puts("게시글이 저장되었습니다.");
                    }

                    free(noNameBo);

                    fclose(noNameBoar);
   

                }
                    break;
                case 3:
                    // 익명 게시판

                    // 게시글 정보 읽어오기
                    FILE *noNameBoardFP = fopen("community.csv", "r");
                    i = 0;
                    Board *noNameBoard = (Board *)malloc(sizeof(Board) * 100);
                    if (noNameBoard == NULL)
                    {
                        error_handling("malloc() error");
                        return -1;
                    }
                    while (fscanf(noNameBoardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", noNameBoard[i].code, &noNameBoard[i].boardNum, noNameBoard[i].id, noNameBoard[i].title, noNameBoard[i].writer, noNameBoard[i].content) == 6)
                    {
                        printf("%s,%d,%s,%s,%s,%s\n", noNameBoard[i].code, noNameBoard[i].boardNum, noNameBoard[i].id, noNameBoard[i].title, noNameBoard[i].writer, noNameBoard[i].content);
                        i++;
                    }
                    ssize_t sent_bytes = send(clnt_sock, noNameBoard, 100 * sizeof(Board), 0);
                    if (sent_bytes == -1)
                    {
                        error_handling("send() error");
                        return -1;
                    }
                    puts("데이터를 클라이언트로 보냈습니다.");

                    // 게시판 번호 or 게시글 페이지 이동 수신
                    int boardNumberChoice;
                    Board boardWrite;
                    Board boardRead;
                    Board saveBoard[100];
                    read(clnt_sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        // 게시글 번호 수신
                        read(clnt_sock, &updateNum, sizeof(updateNum));
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_write = fopen("temp.csv", "w");
                        if (fp_read == NULL || fp_write == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_write);
                            return -1;
                        }

                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", board.code, &board.boardNum, board.id, board.title, board.writer, board.content) == 6)
                        {
                            if (strcmp(board.code, "!@@###3") == 0 && strcmp(board.id, loginUserFromClient.id) == 0 && updateNum == board.boardNum)
                            {

                                updateOrNot = true;
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                                write(clnt_sock, &board, sizeof(board));
                                read(clnt_sock, &board, sizeof(board));
                            }
                            else if (strcmp(board.code, "!@@###3") == 0 && strcmp(board.id, loginUserFromClient.id) != 0 && updateNum == board.boardNum)
                            {
                                // 게시글의 작성자가 아니라면
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                            }

                            fprintf(fp_write, "%s,%d,%s,%s,%s,%s\n", board.code, board.boardNum, board.id, board.title, board.writer, board.content);
                        }

                        fclose(fp_read);
                        fclose(fp_write);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (updateOrNot == true)
                        {
                            puts("게시글이 수정되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        // 게시글 번호
                        int deleteNum;
                        Board saveBoard;
                        long location;
                        bool meetDelete = false;
                        bool deleteOrNot = false;
                        read(clnt_sock, &deleteNum, sizeof(deleteNum));

                        // 게시글 번호에 해당하는 게시글 지우기
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_delete = fopen("temp.csv", "w");
                        if (fp_delete == NULL || fp_read == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_delete);
                            return -1;
                        }
                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^\n]\n", saveBoard.code, &saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content) == 6)
                        {
                            if (strcmp(saveBoard.code, "!@@###3") == 0 && strcmp(saveBoard.id, loginUserFromClient.id) == 0 && saveBoard.boardNum == deleteNum)
                            {
                                // 익명 게시판의 글 중 사용자의 id와 일치하고 입력된 번호와 일치한 글이라면
                                meetDelete = true;
                                deleteOrNot = true;
                            }

                            if (meetDelete == false)
                            {
                                fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                            }
                            if (meetDelete == true && !(strcmp(saveBoard.code, "!@@###3") == 0 && strcmp(saveBoard.id, loginUserFromClient.id) == 0 && saveBoard.boardNum == deleteNum))
                            {
                                if (strcmp(saveBoard.code, "!@@###3") == 0)
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, deleteNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                                    deleteNum++;
                                }
                                else
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                                }
                            }
                        }

                        fclose(fp_read);
                        fclose(fp_delete);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (deleteOrNot == true)
                        {
                            puts("게시글이 삭제되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                        write(clnt_sock, &deleteOrNot, sizeof(deleteOrNot));
                    }
                    else if (boardNumberChoice == 0)
                    {
                        // 게시글 저장
                        read(clnt_sock, &boardWrite, sizeof(boardWrite));
                        FILE *boardFP = fopen("community.csv", "r");
                        i = 0;
                        int freeLastIndex = 0;
                        while (fscanf(boardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", saveBoard[i].code, &saveBoard[i].boardNum, saveBoard[i].id, saveBoard[i].title, saveBoard[i].writer, saveBoard[i].content) == 6)
                        {
                            if (strcmp(saveBoard[i].code, "!@@###3") == 0)
                            {
                                freeLastIndex = saveBoard[i].boardNum;
                                printf("마지막 인덱스 : %d\n", freeLastIndex);
                            }
                            i++;
                        }

                        fclose(boardFP);

                        boardFP = fopen("community.csv", "a");
                        if (boardFP == NULL)
                        {
                            puts("파일 오픈 실패");
                            return -1;
                        }
                        fprintf(boardFP, "%s,%d,%s,%s,%s,%s\n", boardWrite.code, freeLastIndex + 1, loginUserFromClient.id, boardWrite.title, boardWrite.writer, boardWrite.content);
                        fclose(boardFP);
                        puts("게시글이 저장되었습니다.");
                    }

                    free(noNameBoard);

                    fclose(noNameBoardFP);

                    break;
                case 4:
                    // 자유 게시판
                    // 게시글 정보 읽어오기
                    FILE *freeBoardFP = fopen("community.csv", "r");
                    i = 0;
                    Board *freeBoard = (Board *)malloc(sizeof(Board) * 100);
                    if (freeBoard == NULL)
                    {
                        error_handling("malloc() error");
                        return -1;
                    }
                    while (fscanf(freeBoardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", freeBoard[i].code, &freeBoard[i].boardNum, freeBoard[i].id, freeBoard[i].title, freeBoard[i].writer, freeBoard[i].content) == 6)
                    {
                        printf("%s,%d,%s,%s,%s,%s\n", freeBoard[i].code, freeBoard[i].boardNum, freeBoard[i].id, freeBoard[i].title, freeBoard[i].writer, freeBoard[i].content);
                        i++;
                    }
                    ssize_t sent_bytes2 = send(clnt_sock, freeBoard, 100 * sizeof(Board), 0);
                    if (sent_bytes2 == -1)
                    {
                        error_handling("send() error");
                        return -1;
                    }
                    puts("데이터를 클라이언트로 보냈습니다.");

                    // 게시판 번호 or 게시글 페이지 이동 수신
                    boardNumberChoice;
                    Board boardWrite2;
                    read(clnt_sock, &boardNumberChoice, sizeof(boardNumberChoice));

                    if (boardNumberChoice != 0 && boardNumberChoice != 444 && boardNumberChoice != 333)
                    {
                    }
                    else if (boardNumberChoice == 333)
                    {
                        // 글수정
                        int updateNum;
                        bool updateOrNot = false;
                        Board board;
                        // 게시글 번호 수신
                        read(clnt_sock, &updateNum, sizeof(updateNum));
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_write = fopen("temp.csv", "w");
                        if (fp_read == NULL || fp_write == NULL)
                        {
                            puts("파일 오픈 실패");
                            fclose(fp_read);
                            fclose(fp_write);
                            return -1;
                        }

                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", board.code, &board.boardNum, board.id, board.title, board.writer, board.content) == 6)
                        {
                            if (strcmp(board.code, "!@@###4") == 0 && strcmp(board.id, loginUserFromClient.id) == 0 && updateNum == board.boardNum)
                            {

                                updateOrNot = true;
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                                write(clnt_sock, &board, sizeof(board));
                                read(clnt_sock, &board, sizeof(board));
                            }
                            else if (strcmp(board.code, "!@@###4") == 0 && strcmp(board.id, loginUserFromClient.id) != 0 && updateNum == board.boardNum)
                            {
                                // 게시글의 작성자가 아니라면
                                write(clnt_sock, &updateOrNot, sizeof(updateOrNot));
                            }

                            fprintf(fp_write, "%s,%d,%s,%s,%s,%s\n", board.code, board.boardNum, board.id, board.title, board.writer, board.content);
                        }

                        fclose(fp_read);
                        fclose(fp_write);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (updateOrNot == true)
                        {
                            puts("게시글이 수정되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                    }
                    else if (boardNumberChoice == 444)
                    {
                        // 글 삭제
                        // 게시글 번호
                        int deleteNum;
                        Board saveBoard;
                        long location;
                        bool meetDelete = false;
                        bool deleteOrNot = false;
                        read(clnt_sock, &deleteNum, sizeof(deleteNum));

                        // 게시글 번호에 해당하는 게시글 지우기
                        FILE *fp_read = fopen("community.csv", "r");
                        FILE *fp_delete = fopen("temp.csv", "w");
                        if (fp_delete == NULL || fp_read == NULL)
                        {
                            puts("파일 오픈 실패");
                            return -1;
                        }
                        while (fscanf(fp_read, "%[^,],%d,%[^,],%[^,],%[^,],%[^\n]\n", saveBoard.code, &saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content) == 6)
                        {
                            if (strcmp(saveBoard.code, "!@@###4") == 0 && strcmp(saveBoard.id, loginUserFromClient.id) == 0 && saveBoard.boardNum == deleteNum)
                            {
                                // 익명 게시판의 글 중 사용자의 id와 일치하고 입력된 번호와 일치한 글이라면
                                meetDelete = true;
                                deleteOrNot = true;
                            }

                            if (meetDelete == false)
                            {
                                fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                            }
                            if (meetDelete == true && !(strcmp(saveBoard.code, "!@@###4") == 0 && strcmp(saveBoard.id, loginUserFromClient.id) == 0 && saveBoard.boardNum == deleteNum))
                            {
                                if (strcmp(saveBoard.code, "!@@###4") == 0)
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, deleteNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                                    deleteNum++;
                                }
                                else
                                {
                                    fprintf(fp_delete, "%s,%d,%s,%s,%s,%s\n", saveBoard.code, saveBoard.boardNum, saveBoard.id, saveBoard.title, saveBoard.writer, saveBoard.content);
                                }
                            }
                        }

                        fclose(fp_read);
                        fclose(fp_delete);

                        // 기존 파일 삭제 및 임시 파일 이름 변경
                        remove("community.csv");
                        rename("temp.csv", "community.csv");
                        if (deleteOrNot == true)
                        {
                            puts("게시글이 삭제되었습니다.");
                        }
                        else
                        {
                            // 일치하지 않다면
                            puts("해당 회원이 작성한 글이 아닙니다.");
                        }
                        write(clnt_sock, &deleteOrNot, sizeof(deleteOrNot));
                    }
                    else if (boardNumberChoice == 0)
                    {
                        // 게시글 저장
                        read(clnt_sock, &boardWrite, sizeof(boardWrite));
                        FILE *boardFP = fopen("community.csv", "r");
                        i = 0;
                        int freeLastIndex = 0;
                        while (fscanf(boardFP, "%[^,],%d,%[^,],%[^,],%[^,],%[^,\n]\n", saveBoard[i].code, &saveBoard[i].boardNum, saveBoard[i].id, saveBoard[i].title, saveBoard[i].writer, saveBoard[i].content) == 6)
                        {
                            if (strcmp(saveBoard[i].code, "!@@###4") == 0)
                            {
                                freeLastIndex = saveBoard[i].boardNum;
                                printf("마지막 인덱스 : %d\n", freeLastIndex);
                            }
                            i++;
                        }

                        fclose(boardFP);

                        boardFP = fopen("community.csv", "a");
                        if (boardFP == NULL)
                        {
                            puts("파일 오픈 실패");
                            return -1;
                        }
                        fprintf(boardFP, "%s,%d,%s,%s,%s,%s\n", boardWrite.code, freeLastIndex + 1, loginUserFromClient.id, boardWrite.title, boardWrite.writer, boardWrite.content);
                        fclose(boardFP);
                        puts("게시글이 저장되었습니다.");
                    }

                    free(freeBoard);

                    fclose(freeBoardFP);
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

        fclose(userInfo_FP);

        break;
    case 3:
        // 종료
        break;
    default:
        break;
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