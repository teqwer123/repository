#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#define FIVE_MIN 1

//역 구조체
typedef struct
{
    int oddYX[2];//홀수 차 역 좌표
    int evenYX[2];//짝수 차 역 좌표
    char * stationName;// 역 이름
    int taegeuk; // 태극 여부
}Station;


//지하철 구조체
typedef struct
{
    int num;//차번
    Station station;//정차한 역 정보(좌표, 역 이름)
    int stop; //정차 여부 (정차했을 시 1, 정차 안 했을 시 0)
    struct tm* stopTime;//정차를 시작한 시각
    struct tm* movingTime;//노선 이동 시작 시각
} Subway;

Station* MallocStationArray();
void StationNameSetting(Station** stationArrayPtr);
Subway* MallocOddSubway(Station *stationArrayPtr);
void printWay(int (*arr)[40],Subway* oddSubwayArrPtr);


int main(){
    time_t time_p;
    //현재 시각 변수 
    struct tm* localTime_p;

    //홀수 지하철 출발 시각 변수
    struct tm* oddSubwayStartTime;

    //지하철 노선 배열
    int arr[19][40] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,2,1,2,1,2,1,2,2,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,2,1,2,1,2,1,2,2,2},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {2,2,2,2,2,2,3,2,3,2,1,2,1,2,1,2,3,2,3,2,1,2,3,2,3,2,3,2,3,2,1,2,3,2,1,2,1,2,3,2},//3,32
        {2,2,2,2,2,2,3,2,3,2,1,2,1,2,1,2,3,2,3,2,1,2,3,2,3,2,3,2,3,2,1,2,3,2,1,2,1,2,2,3},
        {3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
        {3,2,3,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,1,2,1,2,3,2,3,2,1,2,3,2,1,2,3,2,1,2,3,2,2,2},
        {2,3,3,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,1,2,1,2,3,2,3,2,1,2,3,2,1,2,3,2,1,2,3,2,2,2},
        {2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {2,2,1,2,1,2,1,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {2,2,1,2,1,2,1,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    //역 생성 및 초기화
    Station* stationArrayPtr = MallocStationArray();
    StationNameSetting(&stationArrayPtr);

    //홀수 지하철 구조체 배열 생성 및 초기화
    Subway* oddSubwayArrPtr = MallocOddSubway(stationArrayPtr);

    bool a = false;//테스트하기 위해 임시로 생성한 변수
    while(1){
        
        
        system("clear");

        //현재 시각 가져와서 출력하기
        time_p = time(NULL);
        localTime_p=localtime(&time_p);
        printf("%d시 %d분 %d초 \n", localTime_p->tm_hour, localTime_p->tm_min, localTime_p->tm_sec);

        // 새벽 2시 일때(홀수 지하철 출발 왕십리에 정차)/*일단 1호선만 진행하게 함*/
        if((localTime_p->tm_hour==2&&localTime_p->tm_min==0)||a==false){
            a=true;
            //1호선 정차 시분 2시 0분으로 세팅
            oddSubwayArrPtr[0].stopTime=localTime_p;
            //홀수 지하철 출발 시각
            oddSubwayStartTime = localTime_p;
            //정차
            oddSubwayArrPtr[0].stop = 1;
        }
       
        //왕십리 역에 정차한 후 5분이 지난지 판단하고 5분이 지났다면  한양대 역으로 이동(왕십리역과 한양대역 중간의 노선에서 2분간 존재)
        if((((localTime_p->tm_hour)==(oddSubwayArrPtr[0].stopTime->tm_hour))&&(((localTime_p->tm_min)-(oddSubwayArrPtr[0].stopTime->tm_min))>=FIVE_MIN))||(((localTime_p->tm_hour-1)==(oddSubwayArrPtr[0].stopTime->tm_hour))&&(((localTime_p->tm_min+60)-(oddSubwayArrPtr[0].stopTime->tm_min))>=FIVE_MIN))){
            //시각이 변하지 않고 분만 변할시||시각도 변하고 분도 변할시
            //정차 아님으로 변경
            oddSubwayArrPtr[0].stop = 0;
            //노선이동 시작 시각 갱신
            oddSubwayArrPtr[0].movingTime = localTime_p;
            //왕십리역과 한양대역 중간 노선으로 좌표 이동
            oddSubwayArrPtr[0].station.oddYX[1]++;

            
        }
        

        //지하철 노선 출력
        printWay(arr, oddSubwayArrPtr);

        sleep(5);
    }


    return 0;
}

// 지하철 역 구조체 배열 생성 함수
Station* MallocStationArray()
{
    Station* stationArrayPtr = (Station *)malloc(sizeof(Station) * 51);
    return stationArrayPtr;
}

// 역 구조체 배열에 역 이름 초기화 함수(미완)
void StationNameSetting(Station** stationArrayPtr)
{
    
    char *stationArr[51] = {
        "신설동",
        "용두",
        "신답",
        "용답",
        "합정",
        "홍대입구",
        "신촌",
        "이대",
        "아현",
        "충정로",
        "시청",
        "을지로입구",
        "을지로3가",
        "을지로4가",
        "동대문역사문화공원",
        "신당",
        "상왕십리",
        "왕십리",
        "한양대",
        "뚝섬",
        "성수",
        "건대입구",
        "구의",
        "강변",
        "잠실나루",
        "잠실",
        "신천",
        "종합운동장",
        "삼성",
        "선릉",
        "역삼",
        "강남",
        "교대",
        "서초",
        "방배",
        "사당",
        "낙성대",
        "서울대입구",
        "봉천",
        "신림",
        "신대방",
        "구로디지털단지",
        "대림",
        "신도림",
        "문래",
        "영등포구청",
        "당산",
        "도림천",
        "양천구청",
        "신정네거리",
        "까치산"};
    for (int i = 0; i < 51; i++)
    {
        (*stationArrayPtr)[i].stationName = stationArr[i];
    }

    //태극여부 초기화(태극일 시 1, 아닐 시 0)
    // - 1)신설동
    (*stationArrayPtr)[0].taegeuk = 1;

    // - 2)용두
    (*stationArrayPtr)[1].taegeuk = 0;

    // - 3)신답
    (*stationArrayPtr)[2].taegeuk = 0;

    // - 4)용답
    (*stationArrayPtr)[3].taegeuk = 0;

/*-----------------)--------------------------------*/

    // - 5)합정
    (*stationArrayPtr)[4].taegeuk = 1;
    // - 6)홍대입구
    (*stationArrayPtr)[5].taegeuk = 1;
    // - 7)신촌
    (*stationArrayPtr)[6].taegeuk = 0;
    // - 8)이대
    (*stationArrayPtr)[7].taegeuk = 0;
    // - 9)아현
    (*stationArrayPtr)[8].taegeuk = 0;
    // - 10)충정로
    (*stationArrayPtr)[9].taegeuk = 1;
    // - 11)시청
    (*stationArrayPtr)[10].taegeuk = 1;
    // - 12)을지로입구
    (*stationArrayPtr)[11].taegeuk = 0;
    // - 13)을지로3가
    (*stationArrayPtr)[12].taegeuk = 1;
    // - 14)을지로4가
    (*stationArrayPtr)[13].taegeuk = 1;
    // - 15)동대문역사문화공원
    (*stationArrayPtr)[14].taegeuk = 1;
    // - 16)신당
    (*stationArrayPtr)[15].taegeuk = 1;
    // - 17)상왕십리
    (*stationArrayPtr)[16].taegeuk = 0;
    // - 18)왕십리
    (*stationArrayPtr)[17].taegeuk = 1;
    // - 19)한양대
    (*stationArrayPtr)[18].taegeuk = 0;
    // - 20)뚝섬
    (*stationArrayPtr)[19].taegeuk = 0;
    // - 21)성수
    (*stationArrayPtr)[20].taegeuk = 1;

    /*--------------------------------------*/

    // - 22)건대입구
    (*stationArrayPtr)[21].taegeuk = 1;
    // - 23)구의
    (*stationArrayPtr)[22].taegeuk = 0;
    // - 24)강변
    (*stationArrayPtr)[23].taegeuk = 0;
    // - 25)잠실나루
    (*stationArrayPtr)[24].taegeuk = 0;

    /*-------------)-------------------------*/

    // - 26)잠실
    (*stationArrayPtr)[25].taegeuk = 1;
    // - 27)신천
    (*stationArrayPtr)[26].taegeuk = 0;
    // - 28)종합운동장
    (*stationArrayPtr)[27].taegeuk = 1;
    // - 29)삼성
    (*stationArrayPtr)[28].taegeuk = 0;
    // - 30)선릉
    (*stationArrayPtr)[29].taegeuk = 1;
    // - 31)역삼
    (*stationArrayPtr)[30].taegeuk = 0;
    // - 32)강남
    (*stationArrayPtr)[31].taegeuk = 1;
    // - 33)교대
    (*stationArrayPtr)[32].taegeuk = 1;
    // - 34)서초
    (*stationArrayPtr)[33].taegeuk = 0;
    // - 35)방배
    (*stationArrayPtr)[34].taegeuk = 0;
    // - 36)사당
    (*stationArrayPtr)[35].taegeuk = 1;
    // - 37)낙성대
    (*stationArrayPtr)[36].taegeuk = 0;
    // - 38)서울대입구
    (*stationArrayPtr)[37].taegeuk = 0;
    // - 39)봉천
    (*stationArrayPtr)[38].taegeuk = 0;
    // - 40)신림
    (*stationArrayPtr)[39].taegeuk = 0;
    // - 41)신대방
    (*stationArrayPtr)[40].taegeuk = 0;
    // - 42)구로디지털단지
    (*stationArrayPtr)[41].taegeuk = 0;
    // - 43)대림
    (*stationArrayPtr)[42].taegeuk = 1;
    // - 44)신도림
    (*stationArrayPtr)[43].taegeuk = 1;

/*----------------------------------------------*/

    // - 45)문래
    (*stationArrayPtr)[44].taegeuk = 0;
    // - 46)영등포구청
    (*stationArrayPtr)[45].taegeuk = 1;
    // - 47)당산
    (*stationArrayPtr)[46].taegeuk = 1;

/*-----------------)----------------------------------*/

    // - 48)도림천
    (*stationArrayPtr)[47].taegeuk = 0;
    // - 49)양천구청
    (*stationArrayPtr)[48].taegeuk = 0;
    // - 50)신정네거리
    (*stationArrayPtr)[49].taegeuk = 0;
    // - 51)까치산
    (*stationArrayPtr)[50].taegeuk = 1;


/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/


    //홀수번째 좌표 초기화

    // - 1)신설동
    (*stationArrayPtr)[0].oddYX[0] = 0;
    (*stationArrayPtr)[0].oddYX[1] = 30;

    // - 2)용두
    (*stationArrayPtr)[1].oddYX[0] = 0;
    (*stationArrayPtr)[1].oddYX[1] = 32;

    // - 3)신답
    (*stationArrayPtr)[2].oddYX[0] = 0;
    (*stationArrayPtr)[2].oddYX[1] = 34;

    // - 4)용답
    (*stationArrayPtr)[3].oddYX[0] = 0;
    (*stationArrayPtr)[3].oddYX[1] = 36;

/*-----------------)--------------------------------*/

    // - 5)합정
    (*stationArrayPtr)[4].oddYX[0] = 3;
    (*stationArrayPtr)[4].oddYX[1] = 6;
    // - 6)홍대입구
    (*stationArrayPtr)[5].oddYX[0] = 3;
    (*stationArrayPtr)[5].oddYX[1] = 8;
    // - 7)신촌
    (*stationArrayPtr)[6].oddYX[0] = 3;
    (*stationArrayPtr)[6].oddYX[1] = 10;
    // - 8)이대
    (*stationArrayPtr)[7].oddYX[0] = 3;
    (*stationArrayPtr)[7].oddYX[1] = 12;
    // - 9)아현
    (*stationArrayPtr)[8].oddYX[0] = 3;
    (*stationArrayPtr)[8].oddYX[1] = 14;
    // - 10)충정로
    (*stationArrayPtr)[9].oddYX[0] = 3;
    (*stationArrayPtr)[9].oddYX[1] = 16;
    // - 11)시청
    (*stationArrayPtr)[10].oddYX[0] = 3;
    (*stationArrayPtr)[10].oddYX[1] = 18;
    // - 12)을지로입구
    (*stationArrayPtr)[11].oddYX[0] = 3;
    (*stationArrayPtr)[11].oddYX[1] = 20;
    // - 13)을지로3가
    (*stationArrayPtr)[12].oddYX[0] = 3;
    (*stationArrayPtr)[12].oddYX[1] = 22;
    // - 14)을지로4가
    (*stationArrayPtr)[13].oddYX[0] = 3;
    (*stationArrayPtr)[13].oddYX[1] = 24;
    // - 15)동대문역사문화공원
    (*stationArrayPtr)[14].oddYX[0] = 3;
    (*stationArrayPtr)[14].oddYX[1] = 26;
    // - 16)신당
    (*stationArrayPtr)[15].oddYX[0] = 3;
    (*stationArrayPtr)[15].oddYX[1] = 28;
    // - 17)상왕십리
    (*stationArrayPtr)[16].oddYX[0] = 3;
    (*stationArrayPtr)[16].oddYX[1] = 30;
    // - 18)왕십리
    (*stationArrayPtr)[17].oddYX[0] = 3;
    (*stationArrayPtr)[17].oddYX[1] = 32;
    // - 19)한양대
    (*stationArrayPtr)[18].oddYX[0] = 3;
    (*stationArrayPtr)[18].oddYX[1] = 34;
    // - 20)뚝섬
    (*stationArrayPtr)[19].oddYX[0] = 3;
    (*stationArrayPtr)[19].oddYX[1] = 36;
    // - 21)성수
    (*stationArrayPtr)[20].oddYX[0] = 3;
    (*stationArrayPtr)[20].oddYX[1] = 38;

    /*--------------------------------------*/

    // - 22)건대입구
    (*stationArrayPtr)[21].oddYX[0] = 6;
    (*stationArrayPtr)[21].oddYX[1] = 39;
    // - 23)구의
    (*stationArrayPtr)[22].oddYX[0] = 8;
    (*stationArrayPtr)[22].oddYX[1] = 39;
    // - 24)강변
    (*stationArrayPtr)[23].oddYX[0] = 10;
    (*stationArrayPtr)[23].oddYX[1] = 39;
    // - 25)잠실나루
    (*stationArrayPtr)[24].oddYX[0] = 12;
    (*stationArrayPtr)[24].oddYX[1] = 39;

    /*-------------------------------------*/

    // - 26)잠실
    (*stationArrayPtr)[25].oddYX[0] = 15;
    (*stationArrayPtr)[25].oddYX[1] = 36;
    // - 27)신천
    (*stationArrayPtr)[26].oddYX[0] = 15;
    (*stationArrayPtr)[26].oddYX[1] = 34;
    // - 28)종합운동장
    (*stationArrayPtr)[27].oddYX[0] = 15;
    (*stationArrayPtr)[27].oddYX[1] = 32;
    // - 29)삼성
    (*stationArrayPtr)[28].oddYX[0] = 15;
    (*stationArrayPtr)[28].oddYX[1] = 30;
    // - 30)선릉
    (*stationArrayPtr)[29].oddYX[0] = 15;
    (*stationArrayPtr)[29].oddYX[1] = 28;
    // - 31)역삼
    (*stationArrayPtr)[30].oddYX[0] = 15;
    (*stationArrayPtr)[30].oddYX[1] = 26;
    // - 32)강남
    (*stationArrayPtr)[31].oddYX[0] = 15;
    (*stationArrayPtr)[31].oddYX[1] = 24;
    // - 33)교대
    (*stationArrayPtr)[32].oddYX[0] = 15;
    (*stationArrayPtr)[32].oddYX[1] = 22;
    // - 34)서초
    (*stationArrayPtr)[33].oddYX[0] = 15;
    (*stationArrayPtr)[33].oddYX[1] = 20;
    // - 35)방배
    (*stationArrayPtr)[34].oddYX[0] = 15;
    (*stationArrayPtr)[34].oddYX[1] = 18;
    // - 36)사당
    (*stationArrayPtr)[35].oddYX[0] = 15;
    (*stationArrayPtr)[35].oddYX[1] = 16;
    // - 37)낙성대
    (*stationArrayPtr)[36].oddYX[0] = 15;
    (*stationArrayPtr)[36].oddYX[1] = 14;
    // - 38)서울대입구
    (*stationArrayPtr)[37].oddYX[0] = 15;
    (*stationArrayPtr)[37].oddYX[1] = 12;
    // - 39)봉천
    (*stationArrayPtr)[38].oddYX[0] = 15;
    (*stationArrayPtr)[38].oddYX[1] = 10;
    // - 40)신림
    (*stationArrayPtr)[39].oddYX[0] = 15;
    (*stationArrayPtr)[39].oddYX[1] = 8;
    // - 41)신대방
    (*stationArrayPtr)[40].oddYX[0] = 15;
    (*stationArrayPtr)[40].oddYX[1] = 6;
    // - 42)구로디지털단지
    (*stationArrayPtr)[41].oddYX[0] = 15;
    (*stationArrayPtr)[41].oddYX[1] = 4;
    // - 43)대림
    (*stationArrayPtr)[42].oddYX[0] = 15;
    (*stationArrayPtr)[42].oddYX[1] = 2;
    // - 44)신도림
    (*stationArrayPtr)[43].oddYX[0] = 15;
    (*stationArrayPtr)[43].oddYX[1] = 1;

/*----------------------------------------------*/

    // - 45)문래
    (*stationArrayPtr)[44].oddYX[0] = 11;
    (*stationArrayPtr)[44].oddYX[1] = 0;
    // - 46)영등포구청
    (*stationArrayPtr)[45].oddYX[0] = 8;
    (*stationArrayPtr)[45].oddYX[1] = 0;
    // - 47)당산
    (*stationArrayPtr)[46].oddYX[0] = 5;
    (*stationArrayPtr)[46].oddYX[1] = 0;

/*---------------------------------------------------*/

    // - 48)도림천
    (*stationArrayPtr)[47].oddYX[0] = 18;
    (*stationArrayPtr)[47].oddYX[1] = 2;
    // - 49)양천구청
    (*stationArrayPtr)[48].oddYX[0] = 18;
    (*stationArrayPtr)[48].oddYX[1] = 4;
    // - 50)신정네거리
    (*stationArrayPtr)[49].oddYX[0] = 18;
    (*stationArrayPtr)[49].oddYX[1] = 6;
    // - 51)까치산
    (*stationArrayPtr)[50].oddYX[0] = 18;
    (*stationArrayPtr)[50].oddYX[1] = 8;

    //짝수번째 좌표 초기화
    //------

}

// 홀수 1호선 지하철 구조체 생성 함수
Subway* MallocOddSubway(Station *stationArrayPtr){
    int subwayNum = 1;
    Subway* oddSubwayArr = (Subway*)malloc(sizeof(Subway)*11);

    for(int i = 0 ; i <11 ;i++){
        oddSubwayArr[i].num=subwayNum;
        subwayNum+=2;
        oddSubwayArr[i].station = stationArrayPtr[17];//왕십리 역 
    }
    return oddSubwayArr;
}

//지하철 노선 출력
void printWay(int (*arr)[40],Subway* oddSubwayArrPtr){
    for(int i = 0 ; i < 19; i++){
        for (int j = 0 ; j < 40 ; j++){
            //1호선
            if(oddSubwayArrPtr[0].station.oddYX[0]==i&&oddSubwayArrPtr[0].station.oddYX[1]==j){
                printf("🚃 ");
            }
            // //3호선
            // else if(oddSubwayArrPtr[1].station.oddYX[0]==i&&oddSubwayArrPtr[1].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //5호선
            // else if(oddSubwayArrPtr[2].station.oddYX[0]==i&&oddSubwayArrPtr[2].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //7호선
            // else if(oddSubwayArrPtr[3].station.oddYX[0]==i&&oddSubwayArrPtr[3].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //9호선
            // else if(oddSubwayArrPtr[4].station.oddYX[0]==i&&oddSubwayArrPtr[4].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //11호선
            // else if(oddSubwayArrPtr[5].station.oddYX[0]==i&&oddSubwayArrPtr[5].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //13호선
            // else if(oddSubwayArrPtr[6].station.oddYX[0]==i&&oddSubwayArrPtr[6].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //15호선
            // else if(oddSubwayArrPtr[7].station.oddYX[0]==i&&oddSubwayArrPtr[7].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //17호선
            // else if(oddSubwayArrPtr[8].station.oddYX[0]==i&&oddSubwayArrPtr[8].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //19호선
            // else if(oddSubwayArrPtr[9].station.oddYX[0]==i&&oddSubwayArrPtr[9].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            // //21호선
            // else if(oddSubwayArrPtr[10].station.oddYX[0]==i&&oddSubwayArrPtr[10].station.oddYX[1]==j){
            //     printf("🚃 ");
            // }
            //태극무늬역
            else if(arr[i][j]==3){
                printf("🔴 ");
            }
            //흰색원역
            else if(arr[i][j]==1){
                printf("⚪ ");
            }
            //노선
            else if(arr[i][j]==2){
                printf(" ▪ ");
            }
            //빈공간
            else if(arr[i][j]==0){
                printf("   ");
            }
        }
        printf("\n");
    }
}