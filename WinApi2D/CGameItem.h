#pragma once
#include "CItem.h"

enum class GROUP_GAMEITEM
{
	GOLD_SMALL,
	GOLD_BIG,
	FAIRY_SMALL,
	FAIRY_MIDDLE,
	FAIRY_BIG,
};

class CGameItem : public CItem
{
	GROUP_GAMEITEM m_eGameItem;
public:
	CGameItem(GROUP_GAMEITEM type);
	~CGameItem();

	virtual CGameItem* Clone();

	virtual void ItemAniRender();
};

