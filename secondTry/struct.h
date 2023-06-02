#ifndef __STRUCT_H__
#define __STRUCT_H__
#include <time.h>
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
    int stopTime[2];//정차를 시작한 시각
    int movingTime[2];//노선 이동 시작 시각
    int stationCycleCount[43];//역별 순환횟수 담은 배열
    int stationWayXYArr1[4];//신설동~용답 순환횟수 담은 배열
    int stationWayXYArr2[4];//도림천~까치산 순환횟수 담은 배열

} Subway;

#endif