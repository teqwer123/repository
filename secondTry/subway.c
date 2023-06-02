#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "declaration.h"
#define FIVE_MIN 1 //1분으로 테스트

/*지하철 순환*/
/*운행 시간 : 2:00~24:00*/
/*홀수차 우선 구현*/
/*첫 차 왕십리에서 출발(태극무늬는 5분간 정차)*/
/*다음 역 이동 시 2분 소요*/
/*3의 배수번호 성수역에서 신설동역 들려 되돌아 옴*/
/*각지하철은 출발시 직전차 출발후 8분후에 다음차가 출발 합니다. */
/*각지하철은 현재도착한역 앞쪽역에 앞선 지하철이 있을경우 약 1분간 더 정차후 출발 합니다.*/


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

        // 새벽 2시 일때(홀수 지하철 출발 왕십리에 정차)/*일단 1호선만 진행하게 함*/ 왕십리 정차 횟수가 0일시
        if((localTime_p->tm_hour==2&&localTime_p->tm_min==0)||oddSubwayArrPtr[0].stationCycleCount[0]==0){
            //왕십리 역 순환 횟수 증가
            oddSubwayArrPtr[0].stationCycleCount[0]++;
            //1호선 정차 시분 2시 0분으로 세팅
            oddSubwayArrPtr[0].stopTime[0]=localTime_p->tm_hour;
            oddSubwayArrPtr[0].stopTime[1]=localTime_p->tm_min;
            //홀수 지하철 출발 시각
            oddSubwayStartTime = localTime_p;
            //정차
            oddSubwayArrPtr[0].stop = 1;
        }
       
        //왕십리 역에 정차한 후 5분이 지난지 판단하고 5분이 지났다면  한양대 역으로 이동(왕십리역과 한양대역 중간의 노선에서 2분간 존재)
        if(localTime_p->tm_hour== oddSubwayArrPtr[0].stopTime[0]&&localTime_p->tm_min-oddSubwayArrPtr[0].stopTime[1]>=FIVE_MIN){
            //시각이 변하지 않고 분만 변할시
            //정차 아님으로 변경
            oddSubwayArrPtr[0].stop = 0;
            //노선이동 시작 시각 갱신
            oddSubwayArrPtr[0].movingTime[0] = localTime_p->tm_hour;
            oddSubwayArrPtr[0].movingTime[1] = localTime_p->tm_min;
            //왕십리역과 한양대역 중간 노선으로 좌표 이동
            oddSubwayArrPtr[0].station.oddYX[0]=3;
            oddSubwayArrPtr[0].station.oddYX[1]=33;
        }
        else if(localTime_p->tm_hour!= oddSubwayArrPtr[0].stopTime[0]&&(localTime_p->tm_min+60)-oddSubwayArrPtr[0].stopTime[1]>=FIVE_MIN){
            //시각도 변하고 분도 변할시
            //정차 아님으로 변경
            oddSubwayArrPtr[0].stop = 0;
            //노선이동 시작 시각 갱신
            oddSubwayArrPtr[0].movingTime[0] = localTime_p->tm_hour;
            oddSubwayArrPtr[0].movingTime[1] = localTime_p->tm_min;
            //왕십리역과 한양대역 중간 노선으로 좌표 이동
            oddSubwayArrPtr[0].station.oddYX[0]=3;
            oddSubwayArrPtr[0].station.oddYX[1]=33;
        }

        
        //지하철 노선 출력
        printWay(arr, oddSubwayArrPtr);

        sleep(1);
    }


    return 0;
}