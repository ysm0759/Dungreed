#pragma once

#include "CGameObject.h"
#include "CD2DImage.h"

class CCollider;

enum class GROUP_ATTACK_TYPE
{
	WEAPON,
	SPEAR,
	GUN,
	NONE,
};

class CAttack : public CGameObject
{
	CD2DImage* m_pImg;
	GROUP_ATTACK_TYPE m_eType;
	fPoint m_fColliderSize;
	fPoint m_fImgSize;
	wstring m_sKey;

public:
	CAttack();
	~CAttack();
	virtual CAttack* Clone();
	virtual void render();
	virtual void update();
	void PlayerAttack();

	void MakeAttack(GROUP_ATTACK_TYPE atkType, fPoint colliderSize, fPoint imgSize, wstring key);
	void OnCollisionEnter(CCollider* pOther);
};

