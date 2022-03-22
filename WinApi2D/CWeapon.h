#pragma once


#include "CEquipment.h"



class CWeapon : public CEquipment
{
	
public:
	CWeapon();
	~CWeapon();
	virtual void Attack();
	
};

