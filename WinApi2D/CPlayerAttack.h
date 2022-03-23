#pragma once
#include "CGameObject.h"
#include "CD2DImage.h"


class WeaponAttackInfo;
class CWeapon;

 class CPlayerAttack : public CGameObject
{
private:
	fVec2 m_fvDir;
	float m_fVelocity = 400.f;
	CD2DImage* m_pImg;
	fPoint m_fAniScale;
	wstring m_sKey;
	float m_fDestroyTime;
	float m_fDestroy;
	float m_fRange;

	WeaponAttackInfo* m_pWeaponAttackInfo;



public:
	CPlayerAttack();
	CPlayerAttack(CWeapon* pCurentWeapon);

	 ~CPlayerAttack();
	 virtual CPlayerAttack* Clone();

	 virtual void update();
	 virtual void render();

	 void SetDir(fVec2 vec);
	 void SetDir(float theta);

	 void SetColSize(fPoint size);
	 void SetAniSize(fPoint size);

	 void SetKey(wstring key);

	 void OnCollisionEnter(CCollider* pOther);
};

