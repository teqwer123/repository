#ifndef __USER2_H__
#define __USER2_H__
typedef struct 
{
    //이름, 거주지, ID, PW, 연락처
    char name[20];
    char place[20];
    char id[20];
    char pw[20];
    char phoneNum[20];
} User;
typedef struct {
    //코드,게시글 번호, 작성자의 id,제목, 작성자, 내용
    char code[10];
    int boardNum;
    char id[20];
    char title[50];
    char writer[20];
    char content[500];
} Board;


#endif