#include "framework.h"
#include "CButtonUI.h"

CButtonUI::CButtonUI()
	: CUI(false)
{
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
	m_pImg = nullptr;
	m_strText = L"";
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::Clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::render()
{
	CUI::render();

	if (m_strText.size() > 0)
	{
		CRenderManager::getInst()->RenderText(
			m_strText,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y
		);
	}

	if (nullptr != m_pImg)
	{
		CRenderManager::getInst()->RenderImage(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y
		);
	}
}

void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLbtnDown()
{
}

void CButtonUI::MouseLbtnUp()
{
}

void CButtonUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CButtonUI::SetImage(CD2DImage* img)
{
	m_pImg = img;
}

void CButtonUI::SetText(const wstring& str)
{
	m_strText = str;
}

void CButtonUI::SetClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}
