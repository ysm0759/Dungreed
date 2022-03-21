#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CPlayer.h"

CItem::CItem()
{
	m_cItemStatu = 0;
	
	CreateStatu();
}

CItem::~CItem()
{

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

bool CItem::GetStatu(UINT bit)
{
	return m_cItemStatu & (1 << bit);
}

void CItem::RemoveStatu(UINT bit)
{
	m_cItemStatu &= ~(1 << bit);
}


void CItem::update()
{
	if (GetStatu((UINT)ITEM_STATU::DROP))
	{

	}
	else if (GetStatu((UINT)ITEM_STATU::INVENTORY))
	{

	}
	else if (GetStatu((UINT)ITEM_STATU::WEAR))
	{

	}
}

void CItem::render()
{
	if (GetStatu((UINT)ITEM_STATU::DROP))
	{

	}
	else if (GetStatu((UINT)ITEM_STATU::INVENTORY))
	{

	}
	else if (GetStatu((UINT)ITEM_STATU::WEAR))
	{

	}

}


void CItem::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();


	if (GetStatu((UINT)ITEM_STATU::DROP))
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

