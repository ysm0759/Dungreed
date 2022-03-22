#pragma once


#include "CItem.h"

struct WeaponInfo
{
	int AD;
	int Delay;
};

class CWeapon : public CItem
{
	CD2DImage* m_pImg;
	WeaponInfo m_Info;

public:
	CWeapon();
	~CWeapon();
	virtual void Attack();
	
};

