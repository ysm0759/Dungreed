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

	void SetEquipmentName(wstring name);
	void SetEquipmentEffect(wstring name);
	void SetEquipmentExplanation(wstring name);
	void SetEquipmentItemType(ITEM_TYPE itemType);
	void SetEquipmentItemStat(STAT_INFO statInfo, int data);

};

