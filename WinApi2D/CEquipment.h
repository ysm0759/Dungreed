#pragma once

#include "CItem.h"

enum class ITEM_TYPE
{
	DEFAULT,
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
	wstring m_sExplanation;
	Stat m_cItemStat;


public:
	CEquipment();
	~CEquipment();

	void SetName(string name);
	void SetItemType(ITEM_TYPE itemType);

};

