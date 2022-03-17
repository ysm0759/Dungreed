#pragma once
#include "CGameObject.h"

class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fSpeed; // 배경움직이는 속도
	bool m_isFix;	  // 고정
	bool m_isAuto;	  // 자동으로 움직이는 맵인지 아닌지
	bool m_isDirLeft; // 왼쪽방향인지 기본값 왼쪽
public:
	CBackGround();
	CBackGround( float fSpeed , bool isAuto ,bool isDirLeft = true); // 스피드를 입력하면 이동하는맵 
	~CBackGround();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

