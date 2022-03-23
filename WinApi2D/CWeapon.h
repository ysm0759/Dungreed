#pragma once


#include "CEquipment.h"

enum class ITEM_KIND
{
	DEFAULT,
	SWORD,
	SPEAR,
	GUN,
	SIZE,
};


class CWeapon : public CEquipment
{
	float m_fDelay;
	float m_fRange;
	fPoint m_fColScale;
	ITEM_KIND m_eKind;

public:
	CWeapon();
	~CWeapon();
	virtual void Attack();
	
};

