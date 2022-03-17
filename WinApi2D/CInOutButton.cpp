#include "framework.h"
#include "CInOutButton.h"
#include "CD2DImage.h"

CInOutButton::CInOutButton()
{

	m_pButtonIn = nullptr;
	m_pButtonOut = nullptr;
}

CInOutButton::~CInOutButton()
{


}


void CInOutButton::render()
{

	fPoint pos = GetPos();
	fPoint scale = GetScale();


	if (IsMouseOn())
	{
		if (nullptr == m_pButtonIn)
		{
			return;
		}
		CRenderManager::getInst()->RenderImage(
			m_pButtonIn,
			pos.x ,
			pos.y ,
			pos.x + scale.x ,
			pos.y + scale.y 
		);

	}
	else
	{
		if (nullptr == m_pButtonOut)
		{
			return;
		}
		CRenderManager::getInst()->RenderImage(
			m_pButtonOut,
			pos.x,
			pos.y,
			pos.x + scale.x ,
			pos.y + scale.y 
		);
	}


}



void CInOutButton::ButtonInLoadImg(const wstring& strKey, const wstring& strPath)
{
	m_pButtonIn = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
	SetScale(fPoint(m_pButtonIn->GetWidth() * 4.f, m_pButtonIn->GetHeight() * 4.f));
}

void CInOutButton::ButtonOutLoadImg(const wstring& strKey, const wstring& strPath)
{
	m_pButtonOut = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);

	SetScale(fPoint(m_pButtonOut->GetWidth() * 4.f, m_pButtonOut->GetHeight() * 4.f));
}
