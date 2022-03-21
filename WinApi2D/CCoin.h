#pragma once
#include "CItem.h"

enum class GROUP_COIN
{
	GOLD_SMALL,
	GOLD_BIG,
};

class CCoin : public CItem
{
	GROUP_COIN m_eCoinType;
	
public:
	CCoin();
	CCoin(GROUP_COIN type);
	~CCoin();
	virtual void DropRender();
	virtual void DropUpdate();

};

