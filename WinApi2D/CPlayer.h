#pragma once

#include "CGameObject.h"

class CD2DImage;
class CItem;

class Part
{

};

class CPlayer : public CGameObject
{
private:

	
	CD2DImage* m_pImg;
	float m_fVelocity;
	int m_iPlayerStatu;
	fVec2 m_fDashDir;
	char m_cDashCount;
	char m_cMaxDashCount;
	float m_fCreateDashTime;
	float m_fDashTime;
	list<CItem*> m_inventory;


	void CreateMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual void update();
	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
};

