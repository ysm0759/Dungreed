#pragma once
#include "CUI.h"


class CD2DImage;

enum class BUTTONTYPE
{
	BUTTON_IN,
	BUTTON_OUT,
	BUTTON_CLICK,
	SIZE,
};

class ButtonImageType
{

	CD2DImage* m_pButtonType[(UINT)BUTTONTYPE::SIZE];

public:
	ButtonImageType()
	{
		for (int i = 0; i < (UINT)BUTTONTYPE::SIZE; i++)
		{
			m_pButtonType[i] = nullptr;
		}
	}

	~ButtonImageType() {};

	void SetButton(BUTTONTYPE TYPE, const wstring& strKey, const wstring& strPath)
	{
		m_pButtonType[(UINT)TYPE] = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	}

	CD2DImage* GetButton(BUTTONTYPE TYPE)
	{
		return m_pButtonType[(UINT)TYPE];
	}
};

// 함수포인터를 위한 타입정의
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CButtonUI : public CUI
{
private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

public:
	CButtonUI();
	~CButtonUI();

	virtual CButtonUI* Clone();

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);
};

