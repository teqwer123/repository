#include <stdio.h>
#include <string.h>
#include "user2.h"
int main(){
    FILE * fp = fopen("community.csv", "w");
    Board board;
    Board board1;
    Board board2;
    Board board3;
    Board board4;
    
    strcpy(board.title,"djdjdj");
    strcpy(board1.title,"qwef");
    strcpy(board2.title,"asdfas");
    strcpy(board3.title,"qwefasd");
    strcpy(board4.title,"zxcvzxcv");

    strcpy(board.writer,"dkdkdkd");
    strcpy(board1.writer,";lkjm;lk");
    strcpy(board2.writer,"oiljlkj");
    strcpy(board3.writer,"ugkjkjh");
    strcpy(board4.writer,"qiuhsd");

    strcpy(board.content,"llfkliejflkasd;ilef");
    strcpy(board1.content,"qwasfasijsadlkilef");
    strcpy(board2.content,"lkjasdfoiuwer");
    strcpy(board3.content,"qwerqewfasdfdfkljlkj");
    strcpy(board4.content,"asdioizvkld.wsdfme.");

    fprintf(fp,"%s,%s,%s\n",board.title,board.writer,board.content);
    fprintf(fp,"%s,%s,%s\n",board1.title,board1.writer,board1.content);
    fprintf(fp,"%s,%s,%s\n",board2.title,board2.writer,board2.content);
    fprintf(fp,"%s,%s,%s\n",board3.title,board3.writer,board3.content);
    fprintf(fp,"%s,%s,%s\n",board4.title,board4.writer,board4.content);

    fclose(fp);

    return 0;
}