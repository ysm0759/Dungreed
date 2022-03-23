#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CPlayer.h"
#include "CAnimator.h"



CItem::CItem()
{
	m_cItemStatu = 0;
	m_pImg = nullptr;
	m_eItemType = (GROUP_ITEM)0;
	CreateStatu();
	CreateAnimator();
	CreateCollider();
	SetDrop();
}
CItem* CItem::Clone()
{
	return new CItem(*this);
}

CItem::~CItem()
{

}

void CItem::LoadItemResource()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"GoldSmall", L"texture\\Item\\GoldSmall.png");
	GetAnimator()->CreateAnimation(L"GoldSmall", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7);


	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"GoldBig", L"texture\\Item\\GoldBig.png");
	GetAnimator()->CreateAnimation(L"GoldBig", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7);


	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"FairyS", L"texture\\Item\\FairyS.png");
	GetAnimator()->CreateAnimation(L"FairyS", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16);

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"FairyM", L"texture\\Item\\FairyM.png");
	GetAnimator()->CreateAnimation(L"FairyM", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16);

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"FairyL", L"texture\\Item\\FairyL.png");
	GetAnimator()->CreateAnimation(L"FairyL", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16);
	

	
}

void CItem::SetDrop()
{
	m_cItemStatu = 0;
	SetStatu((UINT)ITEM_STATU::DROP);
}

void CItem::SetInventory()
{
	m_cItemStatu = 0;
	SetStatu((UINT)ITEM_STATU::INVENTORY);
}

void CItem::SetWear()
{
	m_cItemStatu = 0;
	SetStatu((UINT)ITEM_STATU::WEAR);
}

void CItem::SetStatu(UINT bit)
{
	m_cItemStatu |= (1 << bit);
}

bool CItem::IsStatu(UINT bit)
{
	return m_cItemStatu & (1 << bit);
}

void CItem::RemoveStatu(UINT bit)
{
	m_cItemStatu &= ~(1 << bit);
}


void CItem::update()
{

	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		DropUpdate();
	}
	
	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		StatuRemove(GROUP_OBJECT_STATU::GROUND);
		StatuSet(GROUP_OBJECT_STATU::FORCE);
	}

	
	//if (IsStatu((UINT)ITEM_STATU::INVENTORY))
	//{
	//	StatuSet(GROUP_OBJECT_STATU::GROUND);
	//	StatuRemove(GROUP_OBJECT_STATU::FORCE);
	//}


	GetStatu()->update();
	GetAnimator()->update();
	component_render();
}

void CItem::render()
{

	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		DropRender();
	}

}


void CItem::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();


	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		if (pOtherObj->GetName() == L"Player") 
		{
			((CPlayer*)pOtherObj)->EatItem();
		}
		if (pOtherObj->GetName() == L"Monster") //TODO: 나중에 타일로 바꿀것
		{
			StatuSet(GROUP_OBJECT_STATU::GROUND);
			StatuRemove(GROUP_OBJECT_STATU::FORCE);
		}
	}
	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		if (pOtherObj->GetName() == L"Player") 
		{
			((CPlayer*)pOtherObj)->EatItem();
		}
		if (pOtherObj->GetName() == L"Monster") //TODO: 나중에 타일로 바꿀것
		{
			StatuSet(GROUP_OBJECT_STATU::GROUND);
			StatuRemove(GROUP_OBJECT_STATU::FORCE);
		}
	}
}

