#include "framework.h"
#include "CKeyManager.h"

CKeyManager::CKeyManager()
{
	// 키 상태를 모두 눌리지 않은 상태로 초기화
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key]	= false;
		m_arrCurKey[key]	= false;
	}
}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::update()
{
	// 현재 선택(Focus)된 윈도우가 게임 윈도우인가를 확인
	HWND curWnd = GetFocus();
	if (hWnd != curWnd)
	{
		// 윈도우가 선택(Focus)된 상태가 아닐 경우 키입력을 해제시킴
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			m_arrPrevKey[key] = m_arrCurKey[key];
			m_arrCurKey[key] = false;
		}
		return;
	}

	// 모든 키 사이즈만큼 반복하며 입력상태를 확인
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];
		if (GetAsyncKeyState(key) & 0x8000)
		{
			m_arrCurKey[key] = true;
		}
		else
		{
			m_arrCurKey[key] = false;
		}
	}

	// Mouse 좌표 계산
	POINT ptPos = {};
	// GetCursorPos() 윈도우에서 모니터 좌상단 기준 마우스의 좌표를 반환
	GetCursorPos(&ptPos);
	// 모니터 좌상단 기준 마우스 좌표를 게임 윈도우 기준 마우스 위치로 계산
	ScreenToClient(hWnd, &ptPos);

	m_fptCurMousePos = fPoint((float)ptPos.x, (float)ptPos.y);
}

void CKeyManager::init()
{
	
}

bool CKeyManager::GetButton(const int key)
{
	return (true == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CKeyManager::GetButtonUP(const int key)
{
	return (false == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CKeyManager::GetButtonDOWN(const int key)
{
	return (true == m_arrCurKey[key] && false == m_arrPrevKey[key]);
}

fPoint CKeyManager::GetMousePos()
{
	return m_fptCurMousePos;
}

