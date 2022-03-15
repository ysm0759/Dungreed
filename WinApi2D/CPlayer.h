#pragma once

#include "CGameObject.h"

class CD2DImage;



class CPlayer : public CGameObject
{
private:

	
	CD2DImage* m_pImg;
	float m_fVelocity;
	int m_iPlayerStatu;
	char m_cDashCount;
	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
};

