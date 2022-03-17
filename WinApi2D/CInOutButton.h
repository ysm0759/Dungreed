
#pragma once

#include "CButtonUI.h"

class CD2DImage;

class CInOutButton : public CButtonUI
{
private:
	CD2DImage* m_pButtonIn;
	CD2DImage* m_pButtonOut;

public:
	CInOutButton();
	virtual ~CInOutButton();

	virtual void render();

	void ButtonInLoadImg(const wstring& strKey, const wstring& strPath);
	void ButtonOutLoadImg(const wstring& strKey, const wstring& strPath);
};

