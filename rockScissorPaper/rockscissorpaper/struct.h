#ifndef __STRUCT_H__
#define __STRUCT_H__
typedef struct
{
    pthread_t t_id;
    char name[20];
    int xy[2];
    int victory;
    int fail;
} Player;


#endif