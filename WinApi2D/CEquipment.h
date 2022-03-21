#pragma once

#include "CItem.h"

enum class ITEM_TYPE
{
	ONE_HAND_WEAPON,
	TWO_HAND_WEAPON,
	SUB_WEAPON,
	ACCESSORIES,
	SIZE
};

class CEquipment : public CItem
{
protected:
	ITEM_TYPE m_eItemType;
	string m_sName;
	string m_sType;
	string m_sEffect;
	string m_Explanation;



public:
	void SetName(string name);
	void SetItemType(ITEM_TYPE itemType);
	virtual void Attack() {}; // weapon¸¸ ±¸Çö
	virtual void CreateItem();

	//virtual void TakeOn();
	//virtual void TakeOff();
};

