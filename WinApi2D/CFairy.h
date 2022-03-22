#pragma once
#include "CItem.h"

enum class GROUP_FAIRY
{
	FAIRY_SMALL,
	FAIRY_MIDDLE,
	FAIRY_BIG,
};

class CFairy : public CItem
{
	GROUP_FAIRY m_eFairyType;

public:
	CFairy(GROUP_FAIRY type);
	~CFairy();
	virtual void DropRender();
	virtual void DropUpdate();

};

