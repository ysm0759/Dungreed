#pragma once
#include "CGameObject.h"


class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fAutoSpeed;			// 배경움직이는 속도
	float m_fDependOnSpeed;     // 플레이어에 따라 움직이는 배경 속도

	bool m_isFix;			  // true = 고정 ,  false = 아무행동 안해도움직이는 배경  default = true 고정
	bool m_isDirLeft;		  // true = 왼쪽 ,  false = 오른쪽					   default = true 왼쪽
	bool m_isDependOnPlayer;   // 플레이어위치에따라 변동 움직임					   default = flase 고정

public:
	CBackGround();
	~CBackGround();


	void SetFix();
	void SetAuto(float autoSpeed);

	void SetDependOnPlayer(float dependOnSpeed);
	void SetIndependentOnPlayer();

	void SetLeft();
	void SetRight();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();



	void Load(wstring strKey, wstring strPath);
};


