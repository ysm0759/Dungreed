#pragma once

class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	static const int VKEY_SIZE = 0xFF;		// VK의 최대 갯수

	bool m_arrPrevKey[VKEY_SIZE];			// 이전 키의 입력상태
	bool m_arrCurKey[VKEY_SIZE];			// 현재 키의 입력상태
	fPoint m_fptCurMousePos;				// 마우스 좌표

public:
	void update();
	void init();

	bool GetButton(const int key);			// 키가 눌려진 상태 true
	bool GetButtonUP(const int key);		// 키가 올라간 순간 true
	bool GetButtonDOWN(const int key);		// 키가 내려간 순간 true
	fPoint GetMousePos();					// 마우스 좌표 얻기
};

