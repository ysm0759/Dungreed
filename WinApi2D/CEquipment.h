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
	wstring m_sName;
	wstring m_sType;
	wstring m_sEffect;
	wstring m_Explanation;



public:
	CEquipment();
	~CEquipment();

	void SetName(string name);
	void SetItemType(ITEM_TYPE itemType);
	//virtual void Attack() {}; // weapon¸¸ ±¸Çö
	virtual void CreateItem();

};

