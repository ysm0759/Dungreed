#pragma once
#include "CGameObject.h"

class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fSpeed; // 배경움직이는 속도
	bool m_isFix;
public:
	CBackGround();
	CBackGround( float fSpeed ); // 스피드를 입력하면 이동하는맵 
	~CBackGround();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

