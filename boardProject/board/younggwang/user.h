#ifndef __USER_H__
#define __USER_H__

typedef struct{
    //이름, 거주지, ID, PW, 연락처
    char name[20];
    char place[20];
    char id[20];
    char pw[20];
    char phoneNum[20];
} User;

#endif