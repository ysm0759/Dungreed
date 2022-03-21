#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CPlayer.h"
#include "CAnimator.h"



CItem::CItem()
{
	m_cItemStatu = 0;
	CreateStatu();
	CreateAnimator();
}

CItem::~CItem()
{

}

void CItem::RoadItemResource()
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerStand", L"texture\\Item\\CoinSmall.png");
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 5);


	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\Item\\CoinBig.png");
	GetAnimator()->CreateAnimation(L"PlayerRun", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7);


	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\Item\\Fairy.png");
	GetAnimator()->CreateAnimation(L"PlayerJump", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 1);

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
	else if (IsStatu((UINT)ITEM_STATU::INVENTORY))
	{
		InventoryUpdate();
	}
	else if (IsStatu((UINT)ITEM_STATU::WEAR))
	{
		WearUpdate();
	}
}

void CItem::render()
{

	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		DropRender();
	}
	else if (IsStatu((UINT)ITEM_STATU::INVENTORY))
	{
		InventoryRender();
	}
	else if (IsStatu((UINT)ITEM_STATU::WEAR))
	{
		WearRender();
	}

}


void CItem::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();


	if (IsStatu((UINT)ITEM_STATU::DROP))
	{
		if (pOtherObj->GetName() == L"Player") //TODO: 나중에 타일로 바꿀것
		{
			((CPlayer*)pOtherObj)->EatItem();
		}
		if (pOtherObj->GetName() == L"Tile") //TODO: 나중에 타일로 바꿀것
		{
			StatuSet(GROUP_OBJECT_STATU::GROUND);
			StatuRemove(GROUP_OBJECT_STATU::FORCE);
		}
	}
}

