#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"


struct WeaponAttackInfo;
class CWeapon;

 class CPlayerAttack : public CGameObject
{
private:

	fVec2 m_fvDir;
	CD2DImage* m_pImg;
	float m_fDestroy;
	WeaponAttackInfo* m_pWeaponAttackInfo;



public:
	CPlayerAttack();
	CPlayerAttack(CWeapon* pCurentWeapon);
	void SetDir(fVec2 vec);
	virtual ~CPlayerAttack();
	virtual CPlayerAttack* Clone();

	virtual void update();
	virtual void render();

	void SetOffSetPos(fVec2 vec);
	void OnCollisionEnter(CCollider* pOther);
};

