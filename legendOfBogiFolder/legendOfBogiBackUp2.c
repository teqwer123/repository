#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <termios.h>

//던전 포탈 좌표
typedef struct{
    int y;
    int x;
} DeonjeonDoorXY;

//유저팀 수호대 (타수호대 )의 위치 좌표
typedef struct 
{
    int y;
    int x;
} Player_GuardianXY;

//타수호대 구조체 모음
typedef struct 
{
    Player_GuardianXY guardianXY1;
    Player_GuardianXY guardianXY2;
    Player_GuardianXY guardianXY3;
} StructOfGuardians;

//몬스터 좌표 구조체
typedef struct
{
    int y;
    int x;
} MonsterXY;

//몬스터 확률 좌표 배열 생성 함수
int** MonsterAppearanceProbability(){
    int** arr = (int**)malloc((sizeof(int*)*20)*20);
    for(int i = 0 ; i < 20 ; i++){
        arr[i]=(int*)malloc(sizeof(int)*20);
    }
    
    return arr;
}

//몬스터 확률 좌표 난수 담기 함수
int** RandNumIntoMonsterAppearanceProbability(int** arr){
    //확률 담기(33%)
    for(int i = 0 ; i < 20 ; i++){
        for(int j = 0 ; j <20 ; j++){
            arr[i][j]=rand()%10;//0~9
            //초기 생성에서 수호대와 겹치지 않게 생성
            if(i==0&&j==9||i==9&&j==0||i==9&&j==19||i==19&&j==9){
                arr[i][j]=3;
            }
        }
    }

    return arr;
}

//몬스터 확률 좌표 2D배열 메모리 동적할당 해제 함수
void memoryFreeForMonsters(int** monsterProbArr){
    for(int i = 0 ; i < 20 ; i++){
        free(monsterProbArr[i]);
    }
    free(monsterProbArr);
}

//수호대 확률 좌표 2D배열 메모리 동적할당 해제 함수
void memoryFreeForGuardians(int** arr){
    for(int i = 0 ; i < 4 ; i++){
        free(arr[i]);
    }
    free(arr);
}

//수호대 구조체 생성
StructOfGuardians* createGuardObject(int** arr){

    StructOfGuardians* guardian = (StructOfGuardians*)malloc(sizeof(StructOfGuardians));
    guardian->guardianXY1.y = arr[1][0];
    guardian->guardianXY1.x = arr[1][1];
    guardian->guardianXY2.y = arr[2][0];
    guardian->guardianXY2.x = arr[2][1];
    guardian->guardianXY3.y = arr[3][0];
    guardian->guardianXY3.x = arr[3][1];

    if (guardian == NULL) {
        printf("메모리 할당 오류\n");
    }

    memoryFreeForGuardians(arr);

    return guardian;
}

//타수호대 좌표를 랜덤으로 갱신해주는 함수
int RandomUpdateGuardiansXY(){
    
    return rand()%20+2;//2~21
}

//던전맵에서 타수호대 좌표를 랜덤으로 갱신해주는 함수
int RandomUpdateGuardiansXYInDeonJeonMap(){
    return rand()%9+6;//6~14
}

//던전 포탈을 한정된 영역 내에서 랜덤한 좌표값 생성하는 함수
int RandomCreateDoorXY(){
    return rand()%20+2;
}

//유저,타수호대 좌표 랜덤 생성 함수
int** RandomCreatePlayer_GuardianXY(){
    //랜덤 좌표 담기 위한 2차원 배열 동적할당
    int**arr = (int **)malloc(4*sizeof(int*));
    for(int i = 0 ; i<4;i++){
        arr[i] = (int*)malloc(2*sizeof(int));
    }

    //유저와 타수호대의 좌표를 담은 2차원 배열
    int randArr[4][2] = {
        {21,11},//8
        {11,2},
        {2,11},
        {11,21}
    };

    //유저와 타수호대의 좌표를 담은 2차원 배열을 랜덤으로 꺼낼 친구
    int randInt[4]={5};
    
        while (1) {
            randInt[0]=rand()%4;
            randInt[1]=rand()%4;
            randInt[2]=rand()%4;
            randInt[3]=rand()%4;
            if(randInt[0]!=randInt[1]&&randInt[0]!=randInt[2]&&randInt[0]!=randInt[3]&&randInt[1]!=randInt[2]&&randInt[1]!=randInt[3]&&randInt[2]!=randInt[3]) break;
        }

    //동적할당된 2D배열을 가리키는 배열 포인터에 무작위 좌표 대입
    for(int i = 0 ; i< 4 ; i++){
        for(int j = 0 ; j<2;j++){
            arr[i][j]=randArr[randInt[i]][j];
        }
    }
    
    return arr;
}

//키입력 받는 함수
int getch() {
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);  // 현재 터미널 속성 저장
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);  // 입력 모드 변경: 정규 모드 및 에코 비활성화
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 새로운 터미널 속성 설정

    ch = getchar();  // 키 입력 받음

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래 터미널 속성으로 복구

    return ch;
}



//단축키 설정하는 함수
void changeHotkeys(char* hotkeyArr, int* hotKeyCursor){
    char ch = getch();

    if((*hotKeyCursor)==0){
        hotkeyArr[0]=ch;
    }else if((*hotKeyCursor)==1){
        hotkeyArr[1]=ch;
    }else if((*hotKeyCursor)==2){
        hotkeyArr[2]=ch;
    }else if((*hotKeyCursor)==3){
        hotkeyArr[3]=ch;
    }
}

//메뉴창 띄우는 함수
void printMenu(int num, int* menuCursor){
    

}

//단축키 메뉴 창 띄우는 함수
void printHotkeyMenu(int num, int* hotKeyCursor, char* hotkeyArr){
    
}

//화면 지우는 함수
void clearScreen(){
    printf("\033[2J\033[H");
}

//오프닝
void Opening(){
    for(int i = 0 ; i <5 ; i++){
        clearScreen();
        printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■□□□□□□□□□□□□■■■■■■□□□□□■■■■■■□□□□□□□□□□□□□□□□□■\n□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■□□□□□□□□□□□□■□□□□□□□□□□■□□□■■□□□□□□□□□□□□□□□□□□\n□■□□□□□□■■■■■■□■■■■■■□□■■■■■■□■■■■■■□■■■■■■□□□□□■■■■■■□■□□□□□□□□□□■□□□■■□□■■■■■■□■■■■■■□□■\n□■□□□□□□■■□□■■□■■□□■■□□■■□□■■□■■□□■■□■■□□■■□□□□□■■□□■■□■□□□□□□□□□□■■■■■■□□■■□□■■□■■□□■■□□■\n□■□□□□□□■□□□□■□■□□□□■□□■□□□□■□■□□□□■□■□□□□■□□□□□■□□□□■□■■■■■■□□□□□■□□□□■■□■□□□□■□■□□□□■□□■\n□■□□□□□□■■■■■■□■□□□□■□□■■■■■■□■□□□□■□■□□□□■□□□□□■□□□□■□■□□□□□□□□□□■□□□□□■□■□□□□■□■□□□□■□□■\n□■□□□□□□■□□□□□□■□□□□■□□■□□□□□□■□□□□■□■□□□□■□□□□□■□□□□■□■□□□□□□□□□□■□□□□□■□■□□□□■□■□□□□■□□■\n□■□□□□□□■■□□□■□■■□□■■□□■■□□□■□■□□□□■□■■□□■■□□□□□■■□□■■□■□□□□□□□□□□■□□□□■■□■■□□■■□■■□□■■□□■\n□■■■■■■□■■■■■■□■■■■■■□□■■■■■■□■□□□□■□■■■■■■□□□□□■■■■■■□■□□□□□□□□□□■■■■■■■□■■■■■■□■■■■■■□□■\n□□□□□□□□□□□□□□□□□□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■□□□\n□□□□□□□□□□□□□□□□■□□■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■□□■■□□□\n□□□□□□□□□□□□□□□■■■■■■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□■■■■■■□□□\n");
        sleep(1);
        clearScreen();
        printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n■□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■■■■□□□□□□■■■■■□□□□□□■■■■■■■■■■■■■■■■■□\n■□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■■■■□■■■■■■■■■■□■■■□□■■■■■■■■■■■■■■■■■■\n■□■■■■■■□□□□□□■□□□□□□■■□□□□□□■□□□□□□■□□□□□□■■■■■□□□□□□■□■■■■■■■■■■□■■■□□■■□□□□□□■□□□□□□■■□\n■□■■■■■■□□■■□□■□□■■□□■■□□■■□□■□□■■□□■□□■■□□■■■■■□□■■□□■□■■■■■■■■■■□□□□□□■■□□■■□□■□□■■□□■■□\n■□■■■■■■□■■■■□■□■■■■□■■□■■■■□■□■■■■□■□■■■■□■■■■■□■■■■□■□□□□□□■■■■■□■■■■□□■□■■■■□■□■■■■□■■□\n■□■■■■■■□□□□□□■□■■■■□■■□□□□□□■□■■■■□■□■■■■□■■■■■□■■■■□■□■■■■■■■■■■□■■■■■□■□■■■■□■□■■■■□■■□\n■□■■■■■■□■■■■■■□■■■■□■■□■■■■■■□■■■■□■□■■■■□■■■■■□■■■■□■□■■■■■■■■■■□■■■■■□■□■■■■□■□■■■■□■■□\n■□■■■■■■□□■■■□■□□■■□□■■□□■■■□■□■■■■□■□□■■□□■■■■■□□■■□□■□■■■■■■■■■■□■■■■□□■□□■■□□■□□■■□□■■□\n■□□□□□□■□□□□□□■□□□□□□■■□□□□□□■□■■■■□■□□□□□□■■■■■□□□□□□■□■■■■■■■■■■□□□□□□□■□□□□□□■□□□□□□■■□\n■■■■■■■■■■■■■■■■■■■■□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■■\n■■■■■■■■■■■■■■■■□■■□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□■■□□■■■\n■■■■■■■■■■■■■■■□□□□□□■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■□□□□□□■■■\n");
        sleep(1);
    }
    printf("Press any Key >>");
    getch();
    clearScreen();
    printf("\n꿈꾸는 실습실 에서 공주를 구한 복이는 용사의 칭호를 받으며 행복한 나날을 보내지만\n혹시나 하는 악의 무리의 공격에 대비해 4개의 수호대를 결성하고 혹시나하는 악의 침공에 대비했다 \n다음(아무키나 누르세요.)>>");
    getch();
    clearScreen();
    printf("\n어느날밤 하늘에서 떨어진 운석을 조사 하로 용사복이는 길을 떠났다. \n용사 복이가 떠난지 수개월 .....\n다음(아무키나 누르세요.)>>");
    getch();
    clearScreen();
    printf("\n용사복이가 돌아오지 않자 그에 의해 결성된 4개의 수호대는 각각 리더의 명령에 따라 \n용사 복이 행방과 운석이 떨어 진 곳을 조사 하기위해 \n각자의 지역에서 비슷한 시기에 출발하게되는데....\n다음(아무키나 누르세요.)>>");
    getch();
    clearScreen();
    printf("\n그로부터 몇주뒤 각 수호대의 존재는 서로 몰랐던 수호대는 \n각 지역과 미궁의 던젼에서 서로의 존재를 확인 하고 \n적인지 아군인지 모르는 상황에서 전투가 벌어 지고 \n다음(아무키나 누르세요.)>>");
    getch();
    clearScreen();
    printf("\n각 지역 몬스터와 미궁의 던젼의 몬스터와 \n보스몬스터와도 싸우면서 용사복이의 행방과 미궁의 던젼을 조사 해 나간다\n다음(아무키나 누르세요.)>>");
    getch();
    clearScreen();
}

//입력받은 키대로 동작하게 하는 함수
void keyInput(int key, Player_GuardianXY* playerXY,char* hotkeyArr,bool * ifUserMove, bool* menuTF, bool* hotkey, int* menuCursor, int* hotKeyCursor,int playerMovementRange1, int playerMovementRange2){
    //유저 플레이어 이동
    if(key == hotkeyArr[0]&&(*hotkey)==false&&(*menuTF)==false){
        playerXY->y--;
        // 수호대 좌표값 랜덤 생성하기 위한 유저 움직임 파악
        (*ifUserMove)=true;
        if(playerXY->y<playerMovementRange1){
            playerXY->y=playerMovementRange1;
        }
    }else if(key ==hotkeyArr[1]&&(*hotkey)==false&&(*menuTF)==false){
        playerXY->y++;
        // 수호대 좌표값 랜덤 생성하기 위한 유저 움직임 파악
        (*ifUserMove)=true;
        if(playerXY->y>playerMovementRange2){
            playerXY->y=playerMovementRange2;
        }
    }else if(key == hotkeyArr[2]&&(*menuTF)==false){
        playerXY->x--;
        // 수호대 좌표값 랜덤 생성하기 위한 유저 움직임 파악
        (*ifUserMove)=true;
        if(playerXY->x<playerMovementRange1){
            playerXY->x=playerMovementRange1;
        }
    }else if(key ==hotkeyArr[3]&&(*menuTF)==false){
        playerXY->x++;
        // 수호대 좌표값 랜덤 생성하기 위한 유저 움직임 파악
        (*ifUserMove)=true;
        if(playerXY->x>playerMovementRange2){
            playerXY->x=playerMovementRange2;
        }
    }
    
    //메뉴 창 띄우기
    else if(key =='m'){
        (*menuTF)=true;
    }
    //메뉴 창이 떴을 때
    else if(key ==hotkeyArr[0]&&(*menuTF)==true){
        (*menuCursor)--;
        if((*menuCursor)<0){
            (*menuCursor)=0;
        }
    }else if(key==hotkeyArr[1]&&(*menuTF)==true){
        (*menuCursor)++;
        if((*menuCursor)>2){
            (*menuCursor)=2;
        }
    }
    else if(key==' '&&(*hotkey)==false&&(*menuCursor)==0&&(*menuTF)==true){//단축키 메뉴 이동
        (*menuTF)=false;
        (*hotkey)=true;
    }else if(key==' '&&(*hotkey)==false&&(*menuCursor)==1&&(*menuTF)==true){//인벤토리 이동
        //아직 미완
    }else if(key==' '&&(*hotkey)==false&&(*menuCursor)==2&&(*menuTF)==true){//메뉴창 닫기
        (*menuTF)=false;
    }
    //-----

    //단축키 메뉴 창이 떴을 때
    else if(key == hotkeyArr[0]&&(*hotkey)==true){
        (*hotKeyCursor)--;
        if((*hotKeyCursor)<0){
            (*hotKeyCursor)=0;
        }
    }else if(key ==hotkeyArr[1]&&(*hotkey)==true){
        (*hotKeyCursor)++;
        if((*hotKeyCursor)>4){
            (*hotKeyCursor)=4;
        }
    }else if(key==' '&&(*hotkey)==true&&(*hotKeyCursor)==0){//위로이동 키 변경
        changeHotkeys(hotkeyArr, hotKeyCursor);
    }else if(key==' '&&(*hotkey)==true&&(*hotKeyCursor)==1){//아래로이동 키 변경
        changeHotkeys(hotkeyArr, hotKeyCursor);
    }else if(key==' '&&(*hotkey)==true&&(*hotKeyCursor)==2){//왼쪽으로이동 키 변경
        changeHotkeys(hotkeyArr, hotKeyCursor);
    }else if(key==' '&&(*hotkey)==true&&(*hotKeyCursor)==3){//오른쪽으로이동 키 변경
        changeHotkeys(hotkeyArr, hotKeyCursor);
    }else if(key==' '&&(*hotkey)==true&&(*hotKeyCursor)==4){// 뒤로가기
        (*hotkey)=false;
        (*menuTF)=true;
    
    }
    //----
    
}

//일반 맵 출력 함수
void map(int (*map)[24], int (*itemlist)[3], Player_GuardianXY* playerXY, StructOfGuardians** guardians, DeonjeonDoorXY* door, int* battleCount, int* menuCursor, int* hotKeyCursor, bool* menuTF, bool* hotkey, char* hotkeyArr, int** monsterProbArr /*,StructOfMonsterXYARR* structOfMonsterXY*/)  
{

    //24*24 크기의 게임맵 프레임 출력
    for(int i=0; i<24; i++)
    {
        if(map[0][i]==9)
            printf("───");
        else if(map[0][i]==7)
            printf("╭");    
        else  if(map[0][i]==6)
            printf("╮");

    }
    //아이템 리스트 출력
    for(int i=0; i<3; i++)
    {
        if(itemlist[0][i]==9)
            printf("─────────────");
        else if(itemlist[0][i]==6)
            printf("╮\n");
    }
    if((*menuTF)==false&&(*hotkey)==false){
        //메뉴 키가 눌리지 않았을 때,
        for(int i=0; i<24; i++)
            {
                if(map[1][i]==1) 
                    printf("🔥 ");
                else if(map[1][i]==2)    
                    printf("❄  ");
                else if(map[1][i]==8)
                    printf("│");        
            }
    }else if((*menuTF)==true||(*hotkey)==true){
        //메뉴 키가 눌리거나 단축키 설정할 때,
        for(int i = 0 ; i<35; i++){
            if(i==0||i==34){
                printf("│");
            }else{
                printf("💎");
            } 
        }
    }
    
    //아이템 리스트 출력
    for(int i=0; i<3; i++)
    {
        if(itemlist[1][i]==10)
            printf("  보유 아이템 리스트   ");
        else if(itemlist[1][i]==8)
            printf("  │");
        else if(itemlist[1][i]==0)
            printf(" ");            
    }
    printf("\n");  
    
        for(int i=2; i<22; i++)
        {
            for(int j=0; j<24; j++)
            {
                if((*menuTF)==false&&(*hotkey)==false){
                    //메뉴 키가 눌리지 않았을 때,
                    
                    if(door->y==i&&door->x==j){//0~19
                        printf(" 🕳️ ");
                    }
                    //유저 수호대 위치 출력
                    else if(i==playerXY->y&&j==playerXY->x){
                        printf(" 😎");
                    }
                    //타수호대 위치 출력
                    else if(i==(*guardians)->guardianXY1.y&&j==(*guardians)->guardianXY1.x){
                        printf(" 🤓");
                        if(playerXY->y==(*guardians)->guardianXY1.y&&playerXY->x==(*guardians)->guardianXY1.x){
                            
                            //타수호대와 조우한다면 유저 전투횟수 카운트
                            (*battleCount)++;
                            //수호대 위치 좌표 사라짐
                            
                        }
                    }
                    else if(i==(*guardians)->guardianXY2.y&&j==(*guardians)->guardianXY2.x){
                        printf(" 😍");
                        if(playerXY->y==(*guardians)->guardianXY2.y&&playerXY->x==(*guardians)->guardianXY2.x){
                            
                            (*battleCount)++;
                            
                            //수호대 위치 좌표 사라짐
                        }
                    }
                    else if(i==(*guardians)->guardianXY3.y&&j==(*guardians)->guardianXY3.x){
                        printf(" 😁");
                        if(playerXY->y==(*guardians)->guardianXY3.y&&playerXY->x==(*guardians)->guardianXY3.x){
                            
                            (*battleCount)++;
                            
                            //수호대 위치 좌표 사라짐
                        }
                    }
                    else if(i>=18 &&i<=21&&monsterProbArr[playerXY->y-2][playerXY->x-2]<3){//monsterProbArr 은 20*20 사이즈
                        //몬스터를 조우한다면 메시지 출력하기
                        if(j==0){
                            //전투 화면 출력
                            if(i==18||i==21){
                                printf("│******************************************************************│");
                            }else if(i==19){
                                
                                printf("│*몬스터를 조우하셨습니다!                                        *│");
                            }else{
                                printf("│*                                                                *│");
                            }
                        }
                    }
                    //몬스터 출현확률 배열의 해당 확률 요소와 난수가 같다면 몬스터를 출력
                    // else if(monsterProbArr[i-2][j-2]==1&&i<12&&j<12){
                    //     printf(" 👹");
                    // }
                    // else if(monsterProbArr[i-2][j-2]==1&&i<12&&j>=12&&j<22){
                    //     printf(" 👻");
                    // }
                    // else if(monsterProbArr[i-2][j-2]==1&&i>=12&&j<12){
                    //     printf(" 👽");
                    // }
                    // else if(monsterProbArr[i-2][j-2]==1&&i>=12&&j>=12&&j<22){
                    //     printf(" 👾");
                    // }

                    else if(map[i][j]==0)
                        printf("   ");
                    else if(map[i][j]==1)
                        printf("🔥");
                    else if(map[i][j]==2)    
                        printf(" ❄  ");
                    else if(map[i][j]==3)
                        printf("🌳");
                    else if (map[i][j]==4)
                        printf(" 💧 ");    
                    else if(map[i][j]==8)
                        printf("│");
                }else if((*menuTF)==true&&(*hotkey)==false){
                    //메뉴 키가 눌렸을 때,
                    if(j==5){
                        if(i==3){
                            printf("│💎                            메뉴                              💎│");
                        }else if(i==5){
                            if((*menuCursor)==0){
                                printf("│💎 🔶단축키                                                     💎│");
                            }else{
                                printf("│💎   단축키                                                     💎│");
                            }
                        }else if(i==6){
                            if((*menuCursor)==1){
                                printf("│💎 🔶가방                                                       💎│");
                            }else{
                                printf("│💎   가방                                                       💎│");
                            }
                        }else if(i==7){
                            if((*menuCursor)==2){
                                printf("│💎 🔶닫기                                                       💎│");
                            }else{
                                printf("│💎   닫기                                                       💎│");
                            }
                        }
                        else{
                            printf("│💎                                                              💎│");
                        }
                    }
                    
                }else if((*menuTF)==false&&(*hotkey)==true){
                    if(j==5){
                        //단축키 설정할 때,
                        if(i==3){
                            printf("│💎                          단축키 설정                         💎│");
                        }else if(i==5){
                            if((*hotKeyCursor)==0){
                                printf("│💎🔶위로 이동                                                  %c💎│",hotkeyArr[0]);
                            }else{
                                printf("│💎 위로 이동                                                   %c💎│",hotkeyArr[0]);
                            }
                        }else if(i==6){
                            if((*hotKeyCursor)==1){
                                printf("│💎🔶아래로 이동                                                %c💎│",hotkeyArr[1]);
                            }else{
                                printf("│💎 아래로 이동                                                 %c💎│",hotkeyArr[1]);
                            }
                        }else if(i==7){
                            if((*hotKeyCursor)==2){
                                printf("│💎🔶왼쪽으로 이동                                              %c💎│",hotkeyArr[2]);
                            }else{
                                printf("│💎 왼쪽으로 이동                                               %c💎│",hotkeyArr[2]);
                            }
                        }else if(i==8){
                            if((*hotKeyCursor)==3){
                                printf("│💎🔶오른쪽으로 이동                                            %c💎│",hotkeyArr[3]);
                            }else{
                                printf("│💎 오른쪽으로 이동                                             %c💎│",hotkeyArr[3]);
                            }
                        }else if(i==9){
                            if((*hotKeyCursor)==4){
                                printf("│💎🔶뒤로가기                                                    💎│");
                            }else{
                                printf("│💎 뒤로가기                                                     💎│");
                            }
                        }
                        else{
                            printf("│💎                                                              💎│");
                        }
                    }
                    
                }
               
                
            }
            for(int k=0; k<3; k++)
            {
                if(itemlist[i][k]==11)
                    printf(" HP하        ");
                else if(itemlist[i][k]==12)
                    printf(" HP중        ");
                else if(itemlist[i][k]==13)
                    printf(" HP상        ");
                else if(itemlist[i][k]==14)
                    printf(" MP하        ");
                else if(itemlist[i][k]==15)
                    printf(" MP중        ");
                else if(itemlist[i][k]==16)
                    printf(" MP상        ");
                else if(itemlist[i][k]==17)
                    printf(" ALL하       ");
                else if(itemlist[i][k]==18)
                    printf(" All중       ");  
                else if(itemlist[i][k]==19)
                    printf(" All상       ");
                else if(itemlist[i][k]==20)
                    printf(" 부활물약    ");
                else if(itemlist[i][k]==21)
                    printf(" 텐트        ");                   
                else if(itemlist[i][k]==0)
                    printf("             ");
                else if(itemlist[i][k]==8)
                    printf("│");         
            }  
            
            printf("\n");
        }
    
    

    for(int i=0; i<35; i++)
    {
        if((*menuTF)==false&&(*hotkey)==false){
            //메뉴 키가 눌리지 않았을 때,
            if(map[22][i]==3)
                printf("🌳 ");
            else if(map[22][i]==4)   
                printf("💧 "); 
            else if(map[22][i]==8)
                printf("│");  
        }else if((*menuTF)==true||(*hotkey)==true){
            //메뉴 키가 눌렸을 때,
            if(i==0||i==34){
                printf("│");
            }else{
                printf("💎");
            } 
        }
          
    }
    if(itemlist[22][2]==8)
        printf("                          │\n");
    for(int i=0; i<24; i++)
    {
        if(map[23][i]==9)
            printf("───");
        if(map[23][i]==7)
            printf("╰");
        if(map[23][i]==6)
            printf("╯");        
    }
    for(int i=0; i<3; i++)
    {
        if(itemlist[23][i]==9)
            printf("─────────────");
        else if(itemlist[23][i]==6)
            printf("╯\n"); 
    }

    printf("╭──────────────────╮");
    printf("─────────────────╮");
    printf("──────────────────╮");
    printf("─────────────────╮");
    printf("───────────────────╮\n");
    printf("│ 클래스1   이시영 │ 클래스2  이영광 │ 클래스3   원영진 │ 클래스4  박영진 │ 클래스5   박영선  │\n");
    printf("│ HP               │ HP              │ HP               │ HP              │ HP                │\n");
    printf("│ MP               │ MP              │ MP               │ MP              │ MP                │\n");
    printf("│ 1.공격    2.스킬 │  공격     스킬  │  공격      스킬  │  공격     스킬  │  공격      스킬   │\n");
    printf("│ 3.아이템  4.도망 │ 아이템    도망  │ 아이템     도망  │ 아이템    도망  │ 아이템     도망   │\n");
    printf("╰──────────────────╯");
    printf("─────────────────╯");
    printf("──────────────────╯");
    printf("─────────────────╯");
    printf("───────────────────╯\n");

    //몬스터를 조우한다면 유저 전투횟수 카운트
    if(monsterProbArr[playerXY->y-2][playerXY->x-2]<3&&(*menuTF)==false&&(*hotkey)==false){
        if(playerXY->y<12&&playerXY->x<12){
            //불몹 조우
            printf("불몹을 조우했습니다.");
        }else if(playerXY->y-2<10&&playerXY->x-2>=10){
            //눈몹 조우
            printf("눈몹을 조우했습니다.");
        }else if(playerXY->y-2>=10&&playerXY->x-2<10){
            //숲몹 조우
            printf("숲몹을 조우했습니다.");
        }else if(playerXY->y-2>=10&&playerXY->x-2>=10){
            //물몹 조우
            printf("물몹을 조우했습니다.");
        }
        (*battleCount)++;
    }
    //몬스터 출현확률 배열의 해당 확률 요소와 난수가 같다면 몬스터를 출력
    // else if(monsterProbArr[i-2][j-2]==1&&i<12&&j<12){
    //     printf(" 👹");
    // }
    // else if(monsterProbArr[i-2][j-2]==1&&i<12&&j>=12&&j<22){
    //     printf(" 👻");
    // }
    // else if(monsterProbArr[i-2][j-2]==1&&i>=12&&j<12){
    //     printf(" 👽");
    // }
    // else if(monsterProbArr[i-2][j-2]==1&&i>=12&&j>=12&&j<22){
    //     printf(" 👾");
    // }
}

//던전 맵 랜덤 생성 함수
int CreateDeonJeonMapSize(){
    return rand()%4+15;
}

//던전 1층 맵 출력 함수
void deonJeonMap1(bool* doorAppearance,int** monsterProbArr, int deonJeonFloor,MonsterXY* boss,int (*deonJeonMap)[24],int deonJeonMapSize1, int deonJeonMapSize2, int (*itemlist)[3], Player_GuardianXY* playerXY, DeonjeonDoorXY* door, int* battleCount, int* menuCursor, int* hotKeyCursor, bool* menuTF, bool* hotkey, char* hotkeyArr, StructOfGuardians** guardians){
    //24*24 크기의 게임맵 프레임 출력
    for(int i=0; i<24; i++)
    {
        if(deonJeonMap[0][i]==9)
            printf("───");
        else if(deonJeonMap[0][i]==7)
            printf("╭");    
        else  if(deonJeonMap[0][i]==6)
            printf("╮");

    }
    //아이템 리스트 출력
    for(int i=0; i<3; i++)
    {
        if(itemlist[0][i]==9)
            printf("─────────────");
        else if(itemlist[0][i]==6)
            printf("╮\n");
    }
    if((*menuTF)==false&&(*hotkey)==false){
        //메뉴 키가 눌리지 않았을 때,
        for(int i=0; i<23; i++)
            {
                if(deonJeonMap[1][i]==1||2) 
                    printf(" 👁 ");
                else if(deonJeonMap[1][i]==8)
                    printf("│");        
            }
    }else if((*menuTF)==true||(*hotkey)==true){
        //메뉴 키가 눌리거나 단축키 설정할 때,
        for(int i = 0 ; i<35; i++){
            if(i==0||i==34){
                printf("│");
            }else{
                printf("💎");
            } 
        }
    }

    

    //아이템 리스트 출력
    for(int i=0; i<3; i++)
    {
        if(itemlist[1][i]==10)
            printf("  보유 아이템 리스트   ");
        else if(itemlist[1][i]==8)
            printf("  │");
        else if(itemlist[1][i]==0)
            printf(" ");            
    }
    printf("\n");  
    for(int i = 2 ; i<=((24-deonJeonMapSize2)/2);i++){
            for(int j = 0 ; j <24; j++){
                if(i==2){
                    if(j==0)
                        printf("│👁   [던전 %d층]                                                 👁  │",deonJeonFloor);
                }
                else if(j==0||j==23)
                    printf("│");
                else if(j==1||j==22)
                    printf("👁  ");
                else
                    printf("   ");
            }
            printf("\n");
        }
        
        for(int i=2; i<22; i++)
        {
            for(int j=0; j<24; j++)
            {
                if(i>=18 &&i<=21&&monsterProbArr[playerXY->y-2][playerXY->x-2]<3){//monsterProbArr 은 20*20 사이즈
                    //몬스터를 조우한다면 메시지 출력하기
                    if(j==0){
                        //전투 화면 출력
                        if(i==18||i==21){
                            printf("│******************************************************************│");
                        }else if(i==19){
                            
                            printf("│*몬스터를 조우하셨습니다!                                        *│");
                        }else{
                            printf("│*                                                                *│");
                        }
                    }
                }
                else if(i==deonJeonMapSize1-1||i==deonJeonMapSize2+1){
                    if(j>=deonJeonMapSize1&&j<=deonJeonMapSize2){
                        printf("☠  ");
                    }else{
                        printf("   ");
                    }
                }
                else if(i>=deonJeonMapSize1&&i<=deonJeonMapSize2){

                    if((*menuTF)==false&&(*hotkey)==false){
                        //메뉴 키가 눌리지 않았을 때,
                        
                        if(j==deonJeonMapSize1-1||j==deonJeonMapSize2+1){
                            printf(" ☠ ");
                        }
                        else if(door->y==i&&door->x==j&&(*doorAppearance)==true){//0~19
                            printf(" 🕳️ ");
                        }
                        //유저 수호대 위치 출력
                        else if(i==playerXY->y&&j==playerXY->x){
                            printf(" 😎");
                        }
                        //타수호대 위치 출력
                        else if(i==(*guardians)->guardianXY1.y&&j==(*guardians)->guardianXY1.x){
                            printf(" 🤓");
                            if(playerXY->y==(*guardians)->guardianXY1.y&&playerXY->x==(*guardians)->guardianXY1.x){
                                
                                //타수호대와 조우한다면 유저 전투횟수 카운트
                                (*battleCount)++;
                                //수호대 위치 좌표 사라짐
                                
                            }
                        }
                        else if(i==(*guardians)->guardianXY2.y&&j==(*guardians)->guardianXY2.x){
                            printf(" 😍");
                            if(playerXY->y==(*guardians)->guardianXY2.y&&playerXY->x==(*guardians)->guardianXY2.x){
                                
                                (*battleCount)++;
                                
                                //수호대 위치 좌표 사라짐
                            }
                        }
                        else if(i==(*guardians)->guardianXY3.y&&j==(*guardians)->guardianXY3.x){
                            printf(" 😁");
                            if(playerXY->y==(*guardians)->guardianXY3.y&&playerXY->x==(*guardians)->guardianXY3.x){
                                
                                (*battleCount)++;
                                
                                //수호대 위치 좌표 사라짐
                            }
                        }
                        else if(boss->y==i&&boss->x==j){
                            printf(" 👹");
                        }
                        
                        //몬스터 출현확률 배열의 해당 확률 요소와 난수가 같다면 몬스터를 출력
                        // else if(monsterProbArr[i-2][j-2]==1&&i<12&&j<12){
                        //     printf(" 👹");
                        // }
                        // else if(monsterProbArr[i-2][j-2]==1&&i<12&&j>=12&&j<22){
                        //     printf(" 👻");
                        // }
                        // else if(monsterProbArr[i-2][j-2]==1&&i>=12&&j<12){
                        //     printf(" 👽");
                        // }
                        // else if(monsterProbArr[i-2][j-2]==1&&i>=12&&j>=12&&j<22){
                        //     printf(" 👾");
                        // }

                        else if(deonJeonMap[i][j]==0)
                            printf("   ");
                        else if(deonJeonMap[i][j]==1||2||3||4)
                            printf("   ");   
                        else if(deonJeonMap[i][j]==8)
                            printf("│");
                        
                    }else if((*menuTF)==true&&(*hotkey)==false){
                        //메뉴 키가 눌렸을 때,
                        if(j==5){
                            if(i==3){
                                printf("│💎                            메뉴                              💎│");
                            }else if(i==5){
                                if((*menuCursor)==0){
                                    printf("│💎 🔶단축키                                                     💎│");
                                }else{
                                    printf("│💎   단축키                                                     💎│");
                                }
                            }else if(i==6){
                                if((*menuCursor)==1){
                                    printf("│💎 🔶가방                                                       💎│");
                                }else{
                                    printf("│💎   가방                                                       💎│");
                                }
                            }else if(i==7){
                                if((*menuCursor)==2){
                                    printf("│💎 🔶닫기                                                       💎│");
                                }else{
                                    printf("│💎   닫기                                                       💎│");
                                }
                            }
                            else{
                                printf("│💎                                                              💎│");
                            }
                        }
                        
                    }else if((*menuTF)==false&&(*hotkey)==true){
                        if(j==5){
                            //단축키 설정할 때,
                            if(i==3){
                                printf("│💎                          단축키 설정                         💎│");
                            }else if(i==5){
                                if((*hotKeyCursor)==0){
                                    printf("│💎🔶위로 이동                                                  %c💎│",hotkeyArr[0]);
                                }else{
                                    printf("│💎 위로 이동                                                   %c💎│",hotkeyArr[0]);
                                }
                            }else if(i==6){
                                if((*hotKeyCursor)==1){
                                    printf("│💎🔶아래로 이동                                                %c💎│",hotkeyArr[1]);
                                }else{
                                    printf("│💎 아래로 이동                                                 %c💎│",hotkeyArr[1]);
                                }
                            }else if(i==7){
                                if((*hotKeyCursor)==2){
                                    printf("│💎🔶왼쪽으로 이동                                              %c💎│",hotkeyArr[2]);
                                }else{
                                    printf("│💎 왼쪽으로 이동                                               %c💎│",hotkeyArr[2]);
                                }
                            }else if(i==8){
                                if((*hotKeyCursor)==3){
                                    printf("│💎🔶오른쪽으로 이동                                            %c💎│",hotkeyArr[3]);
                                }else{
                                    printf("│💎 오른쪽으로 이동                                             %c💎│",hotkeyArr[3]);
                                }
                            }else if(i==9){
                                if((*hotKeyCursor)==4){
                                    printf("│💎🔶뒤로가기                                                    💎│");
                                }else{
                                    printf("│💎 뒤로가기                                                     💎│");
                                }
                            }
                            else{
                                printf("│💎                                                              💎│");
                            }
                        }
                        
                    }
                
                }else{
                    if(j==0)
                        printf("│👁                                                              👁│");
                }
            }
            for(int k=0; k<3; k++)
            {
                if(itemlist[i][k]==11)
                    printf(" HP하        ");
                else if(itemlist[i][k]==12)
                    printf(" HP중        ");
                else if(itemlist[i][k]==13)
                    printf(" HP상        ");
                else if(itemlist[i][k]==14)
                    printf(" MP하        ");
                else if(itemlist[i][k]==15)
                    printf(" MP중        ");
                else if(itemlist[i][k]==16)
                    printf(" MP상        ");
                else if(itemlist[i][k]==17)
                    printf(" ALL하       ");
                else if(itemlist[i][k]==18)
                    printf(" All중       ");  
                else if(itemlist[i][k]==19)
                    printf(" All상       ");
                else if(itemlist[i][k]==20)
                    printf(" 부활물약    ");
                else if(itemlist[i][k]==21)
                    printf(" 텐트        ");                   
                else if(itemlist[i][k]==0)
                    printf("             ");
                else if(itemlist[i][k]==8)
                    printf("│");         
            }  
            
            printf("\n");
        }
    
    

    for(int i=0; i<35; i++)
    {
        if((*menuTF)==false&&(*hotkey)==false){
            //메뉴 키가 눌리지 않았을 때,
            if(deonJeonMap[22][i]==3||4)
                printf("👁 ");
            else if(deonJeonMap[22][i]==8)
                printf("│");  
        }else if((*menuTF)==true||(*hotkey)==true){
            //메뉴 키가 눌렸을 때,
            if(i==0||i==34){
                printf("│");
            }else{
                printf("💎");
            } 
        }
          
    }
    if(itemlist[22][2]==8)
        printf("                          │\n");
    for(int i=0; i<24; i++)
    {
        if(deonJeonMap[23][i]==9)
            printf("───");
        if(deonJeonMap[23][i]==7)
            printf("╰");
        if(deonJeonMap[23][i]==6)
            printf("╯");        
    }
    for(int i=0; i<3; i++)
    {
        if(itemlist[23][i]==9)
            printf("─────────────");
        else if(itemlist[23][i]==6)
            printf("╯\n"); 
    }

    printf("╭──────────────────╮");
    printf("─────────────────╮");
    printf("──────────────────╮");
    printf("─────────────────╮");
    printf("───────────────────╮\n");
    printf("│ 클래스1   이시영 │ 클래스2  이영광 │ 클래스3   원영진 │ 클래스4  박영진 │ 클래스5   박영선  │\n");
    printf("│ HP               │ HP              │ HP               │ HP              │ HP                │\n");
    printf("│ MP               │ MP              │ MP               │ MP              │ MP                │\n");
    printf("│ 1.공격    2.스킬 │  공격     스킬  │  공격      스킬  │  공격     스킬  │  공격      스킬   │\n");
    printf("│ 3.아이템  4.도망 │ 아이템    도망  │ 아이템     도망  │ 아이템    도망  │ 아이템     도망   │\n");
    printf("╰──────────────────╯");
    printf("─────────────────╯");
    printf("──────────────────╯");
    printf("─────────────────╯");
    printf("───────────────────╯\n");
}

//랜덤한 몬스터 출현확률 배열 생성해서 던전 맵 배열에 넣어주는 함수
void insertRandomNumberDungeonMap(int (*deonJeonMap)[24], int randomNum){
    
    for(int i =(24-(randomNum))/2; i<((24-(randomNum))/2)+randomNum; i++){
        for(int j = (24-(randomNum))/2; j<((24-(randomNum))/2)+randomNum; j++){
            deonJeonMap[i][j] = rand()%10+1;//1~10
        }
    }
    
}

int main(void)
{
    //오프닝
    // Opening();

    int deonJeonMap[24][24]={
        {7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,6},
        {8,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},//2~21
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},//2~21
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},
        {8,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8},//21  map[21][12]
        {8,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,8},
        {7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,6}
    };

    int itemlist[24][3]={
        {9,9,6},
        {0,10,8},
        {11,0,8},
        {12,0,8},
        {13,0,8},
        {14,0,8},
        {15,0,8},
        {16,0,8},
        {17,0,8},
        {18,0,8},
        {19,0,8},
        {20,0,8},
        {21,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {0,0,8},
        {9,9,6}
    };


    //전투 횟수 10번 카운트 여부 확인 변수
    int battleCount = 0;
    
    //단축키 배열
    char hotkeyArr[]={'w','s','a','d'};

    //메뉴 창 띄울 건지 말지 결정하는 변수
    bool menuTF = false;

    //단축키 메뉴 창 띄울 건지 말지 결정하는 변수
    bool hotkey = false;

    //단축키 메뉴에서의 커서 관련 변수
    int hotKeyCursor=0;

    //메뉴에서의 커서 관련 변수
    int menuCursor=0;

    //유저 움직임 체크 변수
    bool ifUserMove = false;

    //수호대와 재대결 피할 수 있게 변수 선언


    srand((int)time(NULL));
    //던전 포탈 좌표 생성
    DeonjeonDoorXY door = {RandomCreateDoorXY(),RandomCreateDoorXY()};

    //동적할당된 무작위 좌표가 들어 있는 2차원 배열을 가리키는 이중 포인터
    int** arr = RandomCreatePlayer_GuardianXY();    

    //유저 플레이어 좌표 선언
    Player_GuardianXY playerXY={arr[0][0],arr[0][1]};

    //타수호대 좌표 선언
    StructOfGuardians* guardians = createGuardObject(arr);
    
    //몬스터 출현확률을 가진 2차원 배열 생성하기
    int** monsterProbArr = MonsterAppearanceProbability();//0~19


    //던전 맵 사이즈 생성
    int mapSize = CreateDeonJeonMapSize();

    //플레이어 이동 범위 설정 변수
    int playerMovementRange1 = 2;
    int playerMovementRange2 = 21;
    
    //일반맵 입장
    while(1){
        //화면지우기
        clearScreen();

        monsterProbArr = RandNumIntoMonsterAppearanceProbability(monsterProbArr);

        //게임맵 출력 -->구조체 배열을 함수의 매개변수로 받고 싶을 때는 구조체 배열의 첫번째 요소의 주소값을 전달하면 된다. 이를 위해서 구조체 배열의 첫번째 요소의 주소를 나타내는 구조체 배열의 이름을 인자로 전달하면 된다.
        
            //일반맵 출력
            map(deonJeonMap,itemlist,&playerXY, &guardians, &door, &battleCount, &menuCursor, &hotKeyCursor, &menuTF, &hotkey, hotkeyArr, monsterProbArr/*, &structOfMonsterXY*/);
        
            //던전 포탈 들어갈 시 다음 던전 입장
            if(door.y==playerXY.y&&door.x==playerXY.x){
                break;
            }
            
        //배틀 10회 달성 시 던전문 위치 랜덤으로 재배치
        printf("배틀횟수: %d\n",battleCount);
        if(battleCount==11){
            door.y = RandomCreateDoorXY();
            door.x = RandomCreateDoorXY();
            battleCount=0;
        }

        //키입력
        int key;
        key = getch();

        keyInput(key,&playerXY,hotkeyArr,&ifUserMove, &menuTF, &hotkey, &menuCursor, &hotKeyCursor, playerMovementRange1, playerMovementRange2);

        //포탈 입장 시 break

        // 유저가 움직일 때마다 수호대 위치 랜덤으로 배치하기
        if (ifUserMove == true&& menuTF!=true && hotkey!=true) {
                guardians->guardianXY1.y = RandomUpdateGuardiansXY();
                guardians->guardianXY1.x = RandomUpdateGuardiansXY();
                guardians->guardianXY2.y = RandomUpdateGuardiansXY();
                guardians->guardianXY2.x = RandomUpdateGuardiansXY();
                guardians->guardianXY3.y = RandomUpdateGuardiansXY();
                guardians->guardianXY3.x = RandomUpdateGuardiansXY();
        }
        
    }

    //던전 입장

    //출력될 던전 층 변수
    int deonJeonFloor=1;
    for(int i = 0 ; i < 5 ; i++){

    
        //던전 1층 입장 전 초기화할 것들 초기화 하기
        
        

        //배틀 횟수 초기화
        battleCount=0;
        
        //던전 배열의 랜덤한 사이즈
        //플레이어 이동 범위 다시 설정
        playerMovementRange2 = rand()%4+15;//15~18
        playerMovementRange1 = (24-playerMovementRange2)/2;//3~4
        
        //플레이어의 위치 랜덤 배치
        playerXY.y=rand()%8+6;
        playerXY.x=rand()%8+6;

        //수호대의 생성될 범위 랜덤하게 생성될 던전맵 사이즈만큼 갱신
        guardians->guardianXY1.y = RandomUpdateGuardiansXYInDeonJeonMap();
        guardians->guardianXY1.x = RandomUpdateGuardiansXYInDeonJeonMap();
        guardians->guardianXY2.y = RandomUpdateGuardiansXYInDeonJeonMap();
        guardians->guardianXY2.x = RandomUpdateGuardiansXYInDeonJeonMap();
        guardians->guardianXY3.y = RandomUpdateGuardiansXYInDeonJeonMap();
        guardians->guardianXY3.x = RandomUpdateGuardiansXYInDeonJeonMap();

        //보스몬스터 좌표 생성
        MonsterXY boss;

        boss.y=10;
        boss.x=10;

        //포탈 생성 여부
        bool doorAppearance = false;

        //던전 1층 입장
        while(1){
            //화면 지우기
            clearScreen();

            //몬스터 출현확률 랜덤변경
            monsterProbArr = RandNumIntoMonsterAppearanceProbability(monsterProbArr);

            //큰 배열 틀(deonJeonMap)에 랜덤한 크기의 던전 맵의 몬스터 출현확률 배열 요소 집어 넣기
            insertRandomNumberDungeonMap(deonJeonMap,playerMovementRange2);

            //던전 1층 출력
            deonJeonMap1(&doorAppearance,monsterProbArr,deonJeonFloor,&boss,deonJeonMap,playerMovementRange1, playerMovementRange2, itemlist, &playerXY, &door, &battleCount,&menuCursor,&hotKeyCursor, &menuTF, &hotkey, hotkeyArr, &guardians);

            if(boss.y==playerXY.y&&boss.x==playerXY.x){
                doorAppearance = true;
            }
            if(doorAppearance==true&&door.y==playerXY.y&&door.x==playerXY.x){
                break;
            }

            //키입력
            int key;
            key = getch();

            keyInput(key,&playerXY,hotkeyArr,&ifUserMove, &menuTF, &hotkey, &menuCursor, &hotKeyCursor, playerMovementRange1, playerMovementRange2);

            // 유저가 움직일 때마다 수호대 위치 랜덤으로 배치하기
            if (ifUserMove == true&& menuTF!=true && hotkey!=true) {
                    guardians->guardianXY1.y = RandomUpdateGuardiansXYInDeonJeonMap();
                    guardians->guardianXY1.x = RandomUpdateGuardiansXYInDeonJeonMap();
                    guardians->guardianXY2.y = RandomUpdateGuardiansXYInDeonJeonMap();
                    guardians->guardianXY2.x = RandomUpdateGuardiansXYInDeonJeonMap();
                    guardians->guardianXY3.y = RandomUpdateGuardiansXYInDeonJeonMap();
                    guardians->guardianXY3.x = RandomUpdateGuardiansXYInDeonJeonMap();
            }
        }
        deonJeonFloor++;
    }

    //수호대를 모두 조우했다면 수호대 구조체 동적할당 해제
    free(guardians);
        
    //몬스터 등장확률 배열 동적할당 해제 시점 고민하기!!!
    memoryFreeForMonsters(monsterProbArr);
    return 0; 
}