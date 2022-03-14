#pragma once
#include "CGameObject.h"

class CD2DImage;

class CMonster : public CGameObject
{
private:
	fPoint m_fptCenterPos;
	float m_fVelocity;
	float m_fDistance;
	bool m_bIsUPDir;

	CD2DImage* m_pImg;

public:
	CMonster();
	~CMonster();
	virtual CMonster* Clone();

	virtual void render();
	virtual void update();

	void SetCenterPos(fPoint point);

	void OnCollisionEnter(CCollider* pOther);
};

