#pragma once
#include "CButtonUI.h"

class CTileButton : public CButtonUI
{
private:
	int m_iIdx;

public:
	CTileButton();
	virtual ~CTileButton();

	virtual void render();

	int GetIdx();
	void SetIdx(int idx);
};

