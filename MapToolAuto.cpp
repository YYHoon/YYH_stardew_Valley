#include "stdafx.h"
#include "MapToolScene.h"

void MapToolScene::Auto()
{
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int cullX = CAMERAMANAGER->getL() / TILESIZE;
			int cullY = CAMERAMANAGER->getT() / TILESIZE;
			int index = (i + cullY) * _horizontal + (j + cullX);

			_vtiles[index].autoIndex = 0;
			_vtiles[index].autoIndex_2 = 0;

			if (_crtSelect == CRTSELECT::TERRAINDRAW)
			{
				if (_vtiles[index].terrain == TERRAIN::GRASS)
				{
					/////////////////  좌
					if (_vtiles[index].rc.left / TILESIZE > 0)
					{
						if (_vtiles[index - 1].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 8;
						}
					}
					/////////////////  우
					if (_vtiles[index].rc.left / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + 1].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 2;
						}
					}
					/////////////////  위
					if (_vtiles[index].rc.top / TILESIZE > 0)
					{
						if (_vtiles[index - _vertical].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 1;
						}
					}
					/////////////////  아래
					if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + _vertical].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 4;
						}
					}
					///////////////// 우 상단
					if (_vtiles[index].rc.top / TILESIZE > 0)
					{
						if (_vtiles[index - _vertical + 1].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 16;
						}
					}
					///////////////// 우 하단
					//if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + _vertical + 1].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 32;
						}
					}
					/////////////////// 좌 상단
					if (_vtiles[index].rc.top / TILESIZE > 0 && _vtiles[index].rc.left / TILESIZE > 0)
					{
						if (_vtiles[index - _vertical - 1].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 128;
						}
					}
					/////////////////// 좌 하단
					//if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + _vertical - 1].terrain == TERRAIN::GRASS)
						{
							_vtiles[index].autoIndex += 64;
						}
					}

					switch (_vtiles[index].autoIndex)
					{
					case 255:

						if (RND->getInt(30) == 0)
						{
							_vtiles[index].terrainframeX = 6;
						}
						else
						{
							_vtiles[index].terrainframeX = RND->getFromIntTo(0, 5);
						}
						_vtiles[index].terrainframeY = 2;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//오른쪽
					case 205:
					case 221:
					case 237:
					case 253:
						_vtiles[index].terrainframeX = 2;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//왼쪽
					case 55:
					case 183:
					case 119:
					case 247:
						_vtiles[index].terrainframeX = 3;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//위
					case 110:
					case 126:
					case 238:
					case 254:
						_vtiles[index].terrainframeX = 1;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//아래
					case 155:
					case 187:
					case 219:
					case 251:
						_vtiles[index].terrainframeX = 0;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//왼아래
					case 19:
					case 51:
					case 82:
					case 83:
					case 87:
					case 179:
					case 147:
					case 211:
					case 215:
						_vtiles[index].terrainframeX = 2;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//왼위
					case 38:
					case 54:
					case 102:
					case 118:
					case 166:
					case 167:
					case 182:
					case 246:
						_vtiles[index].terrainframeX = 0;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//오른위
					case 76:
					case 92:
					case 93:
					case 204:
					case 108:
					case 220:
					case 124:
					case 222:
					case 236:
						_vtiles[index].terrainframeX = 1;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//오른아래
					case 137:
					case 169:
					case 173:
					case 153:
					case 201:
					case 217:
						_vtiles[index].terrainframeX = 3;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						//왼위경사
					case 127:
						_vtiles[index].terrainframeX = 3;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						//오른위경사
					case 239:
						_vtiles[index].terrainframeX = 2;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						//왼아래경사
					case 191:
						_vtiles[index].terrainframeX = 1;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						//오른아래경사
					case 193:
					case 223:
						_vtiles[index].terrainframeX = 0;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						//오른쪽대각 1칸
					case 95:
						_vtiles[index].terrainframeX = 4;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//왼쪽 대각 1칸
					case 175:
						_vtiles[index].terrainframeX = 5;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//위로 1칸
					case 4:
					case 100:
					case 68:
					case 244:
					case 36:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 6;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//왼쪽 1칸
					case 18:
					case 2:
					case 66:
					case 50:
					case 34:
					case 241:
					case 168:
						_vtiles[index].terrainframeX = 5;
						_vtiles[index].terrainframeY = 6;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//오른쪽 1칸
					case 200:
					case 8:
					case 136:
					case 72:
						_vtiles[index].terrainframeX = 4;
						_vtiles[index].terrainframeY = 6;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//아래 1칸
					case 52:
					case 129:
					case 145:
					case 1:
					case 196:
					case 17:
					case 33:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						////////////////////////////////////////////////////////////////////////////////

						//위로 솟아나
					case 111:
						_vtiles[index].terrainframeX = 4;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//아래로 솟아나
					case 159:
						_vtiles[index].terrainframeX = 5;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//오른쪽으로 솟아나
					case 207:
						_vtiles[index].terrainframeX = 5;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//왼쪽으로 솟아나
					case 63:
						_vtiles[index].terrainframeX = 4;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//가로
					case 10:
					case 26:
					case 42:
					case 58:
					case 250:
					case 106:
					case 186:
					case 154:
					case 138:
					case 90:
					case 218:
					case 234:
					case 202:
					case 74:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//세로
					case 101:
					case 149:
					case 69:
					case 181:
					case 5:
					case 85:
					case 53:
					case 245:
					case 213:
					case 117:
					case 197:
					case 229:
					case 21:
					case 133:
					case 37:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						//기억자 <아래
					case 12:
					case 44:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 0;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//기억자 아래>
					case 86:
					case 6:
					case 70:
					case 22:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 0;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//기억자 위>
					case 3:
					case 35:
					case 131:
					case 163:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 1;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//기억자1 <위
					case 9:
					case 25:
					case 73:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 1;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;

						////////////////////////이상한 대각선들
					case 174:
					case 46:
						_vtiles[index].terrainframeX = 0;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 27:
					case 91:
						_vtiles[index].terrainframeX = 1;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 231:
					case 39:
					case 103:
						_vtiles[index].terrainframeX = 2;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 23:
						_vtiles[index].terrainframeX = 3;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 206:
					case 94:
					case 78:
						_vtiles[index].terrainframeX = 4;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 139:
					case 171:
						_vtiles[index].terrainframeX = 5;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 77:
					case 109:
						_vtiles[index].terrainframeX = 6;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					case 189:
					case 141:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 7;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						//////////////////////  세갈래 
						// <아래>
					case 14:
					case 158:
					case 142:
					case 30:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 3;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						// <위>
					case 11:
					case 43:
					case 75:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 6;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						// <위아래
					case 13:
					case 29:
					case 45:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 4;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						// 위아래>
					case 7:
					case 71:
					case 135:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 5;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
						// 사방
					case 15:
						_vtiles[index].terrainframeX = 7;
						_vtiles[index].terrainframeY = 2;
						_vtiles[index].terrain = TERRAIN::GRASS;
						break;
					}
				}

				if (_vtiles[index].terrain == TERRAIN::WATER)
				{
					if (_vtiles[index].rc.left / TILESIZE > 0)
					{
						if (_vtiles[index - 1].terrain == TERRAIN::WATER)
						{
							_vtiles[index].autoIndex += 8;
						}
					}
					/////////////////  우
					if (_vtiles[index].rc.left / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + 1].terrain == TERRAIN::WATER)
						{
							_vtiles[index].autoIndex += 2;
						}
					}
					/////////////////  위
					if (_vtiles[index].rc.top / TILESIZE > 0)
					{
						if (_vtiles[index - _vertical].terrain == TERRAIN::WATER)
						{
							_vtiles[index].autoIndex += 1;
						}
					}
					/////////////////  아래
					if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + _vertical].terrain == TERRAIN::WATER)
						{
							_vtiles[index].autoIndex += 4;
						}
					}
					switch (_vtiles[index].autoIndex)
					{
					case 6:
						_vtiles[index].objectframeX = 4;
						_vtiles[index].objectframeY = 0;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 14 : 
						_vtiles[index].objectframeX = 5;
						_vtiles[index].objectframeY = 0;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 12:
						_vtiles[index].objectframeX = 6;
						_vtiles[index].objectframeY = 0;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 7:
						_vtiles[index].objectframeX = 4;
						_vtiles[index].objectframeY = 1;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 13:
						_vtiles[index].objectframeX = 6;
						_vtiles[index].objectframeY = 1;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 3:
						_vtiles[index].objectframeX = 4;
						_vtiles[index].objectframeY = 2;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 11:
						_vtiles[index].objectframeX = 5;
						_vtiles[index].objectframeY = 2;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					case 9:
						_vtiles[index].objectframeX = 6;
						_vtiles[index].objectframeY = 2;
						_vtiles[index].object = MAPOBJECT::WALL;
						break;
					default:
						_vtiles[index].objectframeX = NULL;
						_vtiles[index].objectframeY = NULL;
						_vtiles[index].object = MAPOBJECT::NONE;
						break;
					}
					
					
					if ((_vtiles[index-_vertical].object == MAPOBJECT::WALL) && (_vtiles[index- _vertical].objectframeX == 5) && (_vtiles[index- _vertical].objectframeY == 0) &&
						(_vtiles[index + 1].object == MAPOBJECT::WALL) && (_vtiles[index + 1].objectframeX == 6) && (_vtiles[index + 1].objectframeY == 0))
					{
						_vtiles[index].objectframeX = 7;
						_vtiles[index].objectframeY = 0;
						_vtiles[index].object = MAPOBJECT::WALL;
					}
				}

			}
			if (_crtSelect == CRTSELECT::TERRAINDRAW_INDOOR)
			{
				if (_vtiles[index].terrain == TERRAIN::WOODEN)
				{
					/////////////////  좌
					if (_vtiles[index].rc.left / TILESIZE > 0)
					{
						if (_vtiles[index - 1].terrain == TERRAIN::WOODEN)
						{
							_vtiles[index].autoIndex += 8;
						}
					}
					/////////////////  우
					if (_vtiles[index].rc.left / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + 1].terrain == TERRAIN::WOODEN)
						{
							_vtiles[index].autoIndex += 2;
						}
					}
					/////////////////  위
					if (_vtiles[index].rc.top / TILESIZE > 0)
					{
						if (_vtiles[index - _vertical].terrain == TERRAIN::WOODEN)
						{
							_vtiles[index].autoIndex += 1;
						}
					}
					/////////////////  아래
					if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
					{
						if (_vtiles[index + _vertical].terrain == TERRAIN::WOODEN)
						{
							_vtiles[index].autoIndex += 4;
						}
					}


					switch (_vtiles[index].autoIndex)
					{
					case 15:
						_vtiles[index].terrainframeX = 1;
						_vtiles[index].terrainframeY = 0;
						_vtiles[index].terrain = TERRAIN::WOODEN;
						break;
					case 12:
						_vtiles[index].terrainframeX = 2;
						_vtiles[index].terrainframeY = 0;
						_vtiles[index].terrain = TERRAIN::WOODEN;
						
					}
				}
			}
			if (_vtiles[index].object == MAPOBJECT::HOETILE)
			{
				/////////////////  좌
				if (_vtiles[index].rc.left / TILESIZE > 0)
				{
					if (_vtiles[index - 1].object == MAPOBJECT::HOETILE)
					{
						_vtiles[index].autoIndex += 8;
					}
				}
				/////////////////  우
				if (_vtiles[index].rc.left / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + 1].object == MAPOBJECT::HOETILE)
					{
						_vtiles[index].autoIndex += 2;
					}
				}
				/////////////////  위
				if (_vtiles[index].rc.top / TILESIZE > 0)
				{
					if (_vtiles[index - _vertical].object == MAPOBJECT::HOETILE)
					{
						_vtiles[index].autoIndex += 1;
					}
				}
				/////////////////  아래
				if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + _vertical].object == MAPOBJECT::HOETILE)
					{
						_vtiles[index].autoIndex += 4;
					}
				}

				switch (_vtiles[index].autoIndex)
				{
				case 0 :
					_vtiles[index].objectframeX = 0;
					_vtiles[index].objectframeY = 0;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
				case 15:
					_vtiles[index].objectframeX = 5;
					_vtiles[index].objectframeY = 3;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////아래
				case 1:
					_vtiles[index].objectframeX = 4;
					_vtiles[index].objectframeY = 0;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////위
				case 4:
					_vtiles[index].objectframeX = 3;
					_vtiles[index].objectframeY = 0;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////오른
				case 2:
					_vtiles[index].objectframeX = 1;
					_vtiles[index].objectframeY = 0;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////왼
				case 8:
					_vtiles[index].objectframeX = 2;
					_vtiles[index].objectframeY = 0;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;

					//////////////////////////////////////////////////////////////
					
					////////////////////세로
				case 5:
					_vtiles[index].objectframeX = 4;
					_vtiles[index].objectframeY = 2;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////가로
				case 10:
					_vtiles[index].objectframeX = 3;
					_vtiles[index].objectframeY = 2;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;

					/////////////////////////////////////////////////////////////////
					
					////////////////////// ㄱ 0,1
				case 6:
					_vtiles[index].objectframeX = 0;
					_vtiles[index].objectframeY = 1;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 1,1
				case 12:
					_vtiles[index].objectframeX = 1;
					_vtiles[index].objectframeY = 1;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 0,2
				case 3:
					_vtiles[index].objectframeX = 0;
					_vtiles[index].objectframeY = 2;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					////////////////////// ㄱ 1,2
				case 9:
					_vtiles[index].objectframeX = 1;
					_vtiles[index].objectframeY = 2;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;

					//////////////////////////////////////////////////////////////////////

					///////////////////////가로 위쪽
				case 14:
					_vtiles[index].objectframeX = 2;
					_vtiles[index].objectframeY = 1;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////가로 아래쪽
				case 11:
					_vtiles[index].objectframeX = 2;
					_vtiles[index].objectframeY = 2;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////세로 오른쪽
				case 7:
					_vtiles[index].objectframeX = 3;
					_vtiles[index].objectframeY = 1;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
					///////////////////////세로 왼쪽
				case 13:
					_vtiles[index].objectframeX = 4;
					_vtiles[index].objectframeY = 1;
					_vtiles[index].object = MAPOBJECT::HOETILE;
					break;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////
			if (_vtiles[index].wet)
			{
				/////////////////  좌
				if (_vtiles[index].rc.left / TILESIZE > 0)
				{
					if (_vtiles[index - 1].wet)
					{
						_vtiles[index].autoIndex_2 += 8;
					}
				}
				/////////////////  우
				if (_vtiles[index].rc.left / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + 1].wet)
					{
						_vtiles[index].autoIndex_2 += 2;
					}
				}
				/////////////////  위
				if (_vtiles[index].rc.top / TILESIZE > 0)
				{
					if (_vtiles[index - _vertical].wet)
					{
						_vtiles[index].autoIndex_2 += 1;
					}
				}
				/////////////////  아래
				if (_vtiles[index].rc.top / TILESIZE < _vertical - 1)
				{
					if (_vtiles[index + _vertical].wet)
					{
						_vtiles[index].autoIndex_2 += 4;
					}
				}

				switch (_vtiles[index].autoIndex_2)
				{
				case 0:
					_vtiles[index].wetframeX = 0;
					_vtiles[index].wetframeY = 3;
					break;
				case 15:
					_vtiles[index].wetframeX = 5;
					_vtiles[index].wetframeY = 4;
					break;
					///////////////////아래
				case 1:
					_vtiles[index].wetframeX = 4;
					_vtiles[index].wetframeY = 3;
					break;
					////////////////////위
				case 4:
					_vtiles[index].wetframeX = 3;
					_vtiles[index].wetframeY = 3;
					break;
					////////////////////오른
				case 2:
					_vtiles[index].wetframeX = 1;
					_vtiles[index].wetframeY = 3;
					break;
					////////////////////왼
				case 8:
					_vtiles[index].wetframeX = 2;
					_vtiles[index].wetframeY = 3;
					break;
				
					//////////////////////////////////////////////////////////////
				
					////////////////////세로
				case 5:
					_vtiles[index].wetframeX = 4;
					_vtiles[index].wetframeY = 5;
					break;
					////////////////////가로
				case 10:
					_vtiles[index].wetframeX = 3;
					_vtiles[index].wetframeY = 5;
					break;
				
					/////////////////////////////////////////////////////////////////
				
					////////////////////// ㄱ 0,1
				case 6:
					_vtiles[index].wetframeX = 0;
					_vtiles[index].wetframeY = 4;
					break;
					////////////////////// ㄱ 1,1
				case 12:
					_vtiles[index].wetframeX = 1;
					_vtiles[index].wetframeY = 4;
					break;
					////////////////////// ㄱ 0,2
				case 3:
					_vtiles[index].wetframeX = 0;
					_vtiles[index].wetframeY = 5;
					break;
					////////////////////// ㄱ 1,2
				case 9:
					_vtiles[index].wetframeX = 1;
					_vtiles[index].wetframeY = 5;
					break;
				
					//////////////////////////////////////////////////////////////////////
				
					///////////////////////가로 위쪽
				case 14:
					_vtiles[index].wetframeX = 2;
					_vtiles[index].wetframeY = 4;
					break;
					///////////////////////가로 아래쪽
				case 11:
					_vtiles[index].wetframeX = 2;
					_vtiles[index].wetframeY = 5;
					break;
					///////////////////////세로 오른쪽
				case 7:
					_vtiles[index].wetframeX = 3;
					_vtiles[index].wetframeY = 4;
					break;
					///////////////////////세로 왼쪽
				case 13:
					_vtiles[index].wetframeX = 4;
					_vtiles[index].wetframeY = 4;
					break;
				}
			}
		}
	}
}
