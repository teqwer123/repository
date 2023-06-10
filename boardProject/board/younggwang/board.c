#include <stdio.h>
#include <string.h>
//회원가입 정보 구조체
typedef struct
{
    char id[20];
    char pw[20];
} User;
int main(){
    int yes;
    fputs("회원가입하시겠습니까? 1.예 2.아니오\n",stdout);
    scanf("%d",&yes);
    if(yes==1){
        //회원가입 로직
        FILE * joinfp;
        User userInfo;

        joinfp = fopen("userInfo.bin", "wb");
        if(joinfp==NULL){
            puts("파일오픈 실패");
            return -1;
        }

        puts("아이디 입력(20자 이내): ");
        scanf("%s", userInfo.id);
        fgetc(stdin);
        puts("비밀번호 입력: ");
        scanf("%s",userInfo.pw);
        fgetc(stdin);
        fwrite((void*)&userInfo, sizeof(userInfo),1, joinfp);
        fclose(joinfp);
    }
    if(yes==2){
        //로그인 로직
        FILE * loginfp;
        User userInfo;
        char id[20];
        char pw[20];

        loginfp = fopen("userInfo.bin", "rb");
        if(loginfp==NULL){
            puts("파일오픈 실패");
            return -1;
        }
        

        fread((void*)&userInfo, sizeof(userInfo),1 , loginfp);

        puts("ID 입력 : ");

        // fgets(id,sizeof(id),stdin);
        scanf("%s", id);
        if(strcmp(userInfo.id,id)==0){
            puts("ID가 일치합니다.");
            puts("PW 입력 : ");
            // fgets(pw, sizeof(pw),stdin);
            scanf("%s",pw);
            if(strcmp(userInfo.pw,pw)==0){
                puts("PW가 일치합니다.");
                puts("로그인되었습니다.");
            }

        }

    }
    if(yes!=1&&yes!=2){
        fputs("잘못된 입력\n",stdout);
    }
    return 0;
}