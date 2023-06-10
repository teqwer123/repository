#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // 서버 IP 주소
#define SERVER_PORT 12345     // 서버 포트 번호
#define BUFFER_SIZE 1024

typedef struct {
    char username[20];
    char password[20];
} UserInfo;

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];

    // UDP 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    // 소켓에 주소 바인딩
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", SERVER_PORT);

    // 파일 포인터 생성
    FILE* fp = fopen("user_info.txt", "a");
    if (fp == NULL) {
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 클라이언트로부터 회원가입 정보 수신
        client_len = sizeof(client_addr);
        ssize_t num_bytes = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &client_len);
        if (num_bytes < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        // 수신한 회원가입 정보 저장
        UserInfo user;
        memcpy(&user, buffer, sizeof(UserInfo));
        fprintf(fp, "Username: %sPassword: %s\n", user.username, user.password);
        fflush(fp);

        printf("User registration successful.\n");
    }

    // 파일 포인터 닫기
    fclose(fp);
    close(sockfd);
    return 0;
}