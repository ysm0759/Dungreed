#include "framework.h"
#include "CItem.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CPlayer.h"
#include "CAnimator.h"

CItem* CItem::Clone()
{
	return new CItem(*this);
}


CItem::CItem()
{
	m_cItemStatu = 0;
	m_pImg = nullptr;
	m_sKey = L"";


	//드랍될때 방향 , 힘
	if (0 == rand() % 2)
		m_fDir = fPoint((float)-rand(), (float)-rand());
	else
		m_fDir = fPoint((float)rand(), (float)-rand());
	
	m_fForce = (float)(rand() % 200 + 400);
	
	CreateStatu();
	GetStatu()->SetForceDir(m_fDir);
	GetStatu()->SetForce(m_fForce);
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

void CItem::SetStay()
{
	m_cItemStatu = 0;
	SetStatu((UINT)ITEM_STATU::STAY);
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
		StatuRemove(GROUP_OBJECT_STATU::GROUND);
		StatuSet(GROUP_OBJECT_STATU::FORCE);
	}

	if (IsStatu((UINT)ITEM_STATU::STAY))
	{
		StatuSet(GROUP_OBJECT_STATU::GROUND);
		StatuRemove(GROUP_OBJECT_STATU::FORCE);
	}
	if (IsStatu((UINT)ITEM_STATU::INVENTORY))
	{

	}


	GetStatu()->update();
	GetAnimator()->update();
}

void CItem::render()
{
	this->GetAnimator()->Play(m_sKey, GetScale());
	component_render();
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
		if (pOtherObj->GetName() == L"Tile") //TODO: 아이템 collider
		{
			SetStatu((UINT)ITEM_STATU::STAY);
		}
	}
}

