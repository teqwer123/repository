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
    struct tm* stopTime;//정차를 시작한 시각
    struct tm* movingTime;//노선 이동 시작 시각
} Subway;

#endif