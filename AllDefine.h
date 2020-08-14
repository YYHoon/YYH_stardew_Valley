#pragma once

#define MAGENTA RGB(255,0,255)
#define CYAN RGB(0,255,255)
#define YELLOW RGB(255,255,0)
#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)

//////////////////////////////
#define RadToDeg (float)180/PI        // 라디안 -> 디그리
#define DegToRad (float)PI/180		  // 디그리 -> 라디안

//////////////////////////////
#define IMAGECOOR 376, 126

#define TILESIZE 64	//타일 사이즈

/////////////////////////////
#define LOADINGMAX 1500	
////////////////////////////
#define INVENIMAGECOOR 376, 126			//인벤토리 이미지 위치 값
#define ALPHAVALUEMAX 230				//어두워졌을 때 최대 알파값
#define REALTIMEMAX 20					//게임 속 최대 시간, [원래 인게임 시간은 860]
#define REALTIMEHALF REALTIMEMAX / 2	//게임 속 최대 시간의 반 낮/밤 기준
#define ALPHADELAY REALTIMEMAX / 10		//알파렌더 딜레이값
#define CLOCKMOVEDANGLE 0.029f			//시계 각도 변화 속도
#define CLOCKTIMEMAX 109				//시계 최대 값
#define CLOCKTIMEHALF CLOCKTIMEMAX / 2	//시계 사이 값
//////////////////////////////