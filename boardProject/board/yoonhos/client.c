#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // 서버 IP 주소
#define SERVER_PORT 12345     // 서버 포트 번호

typedef struct {
    char username[20];
    char password[20];
} UserInfo;

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // UDP 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // 회원가입 정보 입력 받기
    UserInfo user;
    printf("Enter username: ");
    fgets(user.username, sizeof(user.username), stdin);
    printf("Enter password: ");
    fgets(user.password, sizeof(user.password), stdin);

    // 회원가입 정보 서버에 전송
    if (sendto(sockfd, &user, sizeof(user), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("User registration request sent.\n");

    close(sockfd);
    return 0;
}