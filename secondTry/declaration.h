#ifndef __DECLARATION_H__
#define __DECLARATION_H__
#include "struct.h"


Station* MallocStationArray();
void StationNameSetting(Station** stationArrayPtr);
Subway* MallocOddSubway(Station *stationArrayPtr);
void printWay(int (*arr)[40],Subway* oddSubwayArrPtr);


/*지하철 순환*/
/*운행 시간 : 2:00~24:00*/
/*홀수차 우선 구현*/
/*첫 차 왕십리에서 출발(태극무늬는 5분간 정차)*/
/*다음 역 이동 시 2분 소요*/
/*3의 배수번호 성수역에서 신설동역 들려 되돌아 옴*/
/*각지하철은 출발시 직전차 출발후 8분후에 다음차가 출발 합니다. */
/*각지하철은 현재도착한역 앞쪽역에 앞선 지하철이 있을경우 약 1분간 더 정차후 출발 합니다.*/


#endif