#include "framework.h"
#include "CGameItem.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"


CGameItem* CGameItem::Clone()
{
	return new CGameItem(*this);
}

CGameItem::CGameItem(GROUP_GAMEITEM type)
{


	CreateCollider();
	CreateAnimator();
	this->m_eGameItem = type;
	switch (type)
	{
	case GROUP_GAMEITEM::GOLD_SMALL:
		this->m_sKey = L"GoldSmall";		     // 애니메이션 파일 이름
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //이미지 불러오기
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7); //편집
		SetScale(fPoint(30, 30));				 // 애니메이션 크기
		GetCollider()->SetScale(fPoint(30, 30)); // 애니메이션 콜라이더 크기
		SetDrop();
		break;
	case GROUP_GAMEITEM::GOLD_BIG:
		this->m_sKey = L"GoldBig";				 // 애니메이션 파일 이름
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //이미지 불러오기
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7); //편집
		SetScale(fPoint(30, 30));				 // 애니메이션 크기
		GetCollider()->SetScale(fPoint(30, 30)); // 애니메이션 콜라이더 크기
		SetDrop();
		break;
	case GROUP_GAMEITEM::FAIRY_SMALL:
		this->m_sKey = L"FairyS";				 // 애니메이션 파일 이름
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //이미지 불러오기
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16); //편집
		SetScale(fPoint(30, 30));				 // 애니메이션 크기
		GetCollider()->SetScale(fPoint(30, 30)); // 애니메이션 콜라이더 크기
		SetStay();
		break;
	case GROUP_GAMEITEM::FAIRY_MIDDLE:
		this->m_sKey = L"FairyM";				 // 애니메이션 파일 이름
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //이미지 불러오기
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16); //편집
		SetScale(fPoint(30, 30));				 // 애니메이션 크기
		GetCollider()->SetScale(fPoint(30, 30)); // 애니메이션 콜라이더 크기
		SetStay();
		break;
	case GROUP_GAMEITEM::FAIRY_BIG:
		this->m_sKey = L"FairyL";				 // 애니메이션 파일 이름
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //이미지 불러오기
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16); //편집
		SetScale(fPoint(30, 30));				 // 애니메이션 크기
		GetCollider()->SetScale(fPoint(30, 30)); // 애니메이션 콜라이더 크기
		SetStay();
		break;
	}

}	

CGameItem::~CGameItem()
{

}


void CGameItem::ItemAniRender()
{

};


