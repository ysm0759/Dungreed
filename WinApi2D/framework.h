// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "Msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include <assert.h>

// STL
#include <vector>
#include <map>
#include <list>

using namespace std;

// Util
#include "SingleTon.h"
#include "struct.h"
#include "Logger.h"

//========================================
//## 게임 그룹						##
//========================================

enum class GROUP_GAMEOBJ
{
	DEFAULT,
	MAP, //나중에 지우던지 하면 됨
	BACK_GROUND,

	TILE,

	MONSTER,
	MONSTER_ATTACK,


	PLAYER_ATTACK,
	PLAYER_MISSILE,
	PLAYER_WEAPON_BACK,
	PLAYER,
	PLAYER_WEAPON_FRONT,
	ITEM, //TODO 나중에 옮길것

	UI,		// UI는 모든 게임오브젝트 중 최상단 Layer에 위치
	SIZE,
};

enum class GROUP_SCENE
{
	TOOL,
	MAIN,
	LOAD,
	START,
	BILLIZE,
	BILLIZE_ESC,
	VILLAGE,
	STAGE,


	TEST,
	SIZE,
};



enum class GROUP_OBJECT_STATU
{
	JUMP,  // 점프한 상태
	GROUND,// 바닥에 붙어있는 상태
	MOVE,  // 움직이는 상태
	FORCE, // 힘의 방향으로 날라가는
	FLY,   // 중력을 받지 않고 계속 날라다니는 객체
	LOOK,  // 값이 차있으면 왼쪽 값이 비어있으면 오른쪽 
	ATTACK,// 공격중인 상태
	DOWN,  // 하강상태

};
enum class GROUP_TILE
{
	NONE,
	GROUND,

	WALL_LEFT,
	WALL_RIGHT,


	PLATFORM, 
	PLATFORM_BOTTOM,

	SLOPE,
	SLOPE_PLATFORM,

	DOOR_LEFT,
	DOOR_RIGHT,
	DOOR_UP,
	DOOR_DOWN,
	DOOR_DUNGEON,

	CAMERA_POS_LEFT_BOTTOM,
	CAMERA_POS_RIGHT_TOP,

	SIZE,
};
//========================================
//## 이벤트 타입					##
//========================================

enum class TYPE_EVENT
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,

	SIZE,
};

enum class BACK_OPTION
{
	FIX,		// 고정
	DEPEND_ON,	// 오브젝트 의존


	AUTO,		// 자동으로움직임
	REPEAT,		// 무한 반복
	LEFT,		// 왼쪽으로 이동
	RIGHT,		// 오른쪽으로 이동
	UP,			// 위로이동
	DOWN,		// 아래로이동
};


#define eBRUSH	TYPE_BRUSH
enum class TYPE_BRUSH
{
	HOLLOW,

	SIZE
};

#define ePEN		TYPE_PEN
enum class TYPE_PEN
{
	RED,
	GREEN,
	BLUE,
	WHITE,

	SIZE
};

#define eFONT	TYPE_FONT
enum class TYPE_FONT
{
	COMIC24,		// 개발자 mode 정보 출력용 폰트
	COMIC28,			// state 출력용 폰트
	COMIC18,

	SIZE
};

#define eSHAPE	COLL_SHAPE
enum class COLL_SHAPE
{
	CIRCLE,
	RECT,
	POINT,

	END
};

// Core & Manager
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"
#include "CRenderManager.h"

//========================================
//##			디파인문				##
//========================================

#define WINSTARTX   100
#define WINSTARTY   100
//#define WINSIZEX		1280
//#define	WINSIZEY	720
static float WINSIZEX = 1280;
static float WINSIZEY = 720;

#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX


#define DT				CTimeManager::getInst()->GetDT()
#define fDT				CTimeManager::getInst()->GetfDT()

#define Key(key)		CKeyManager::getInst()->GetButton(key)
#define KeyUp(key)		CKeyManager::getInst()->GetButtonUP(key)
#define KeyDown(key)	CKeyManager::getInst()->GetButtonDOWN(key)

#define MousePos()		CKeyManager::getInst()->GetMousePos()

#define CreateObj(pObj, group)	CEventManager::getInst()->EventCreateObject(pObj, group)
#define DeleteObj(pObj)			CEventManager::getInst()->EventDeleteObject(pObj)
#define ChangeScn(scene)		CEventManager::getInst()->EventChangeScene(scene)

#define StatuSet(statu) CGameObject::GetStatu()->SetStatu((UINT)statu)
#define StatuGet(statu) CGameObject::GetStatu()->IsStatu((UINT)statu)
#define StatuRemove(statu) CGameObject::GetStatu()->RemoveStatu((UINT)statu)

#define ZOOM		   CCameraManager::getInst()->GetZoom()
#define SetZOOM(zoom)		   CCameraManager::getInst()->SetZoom(zoom)

//========================================
//## 전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

