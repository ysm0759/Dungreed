#pragma once
#include "CGameObject.h"

enum class GROUP_ITEM
{
	GOLD_SMALL,
	GOLD_BIG,
	FAIRY,
	SWORD,
	SPEAR,
	GUN,

};

enum class ITEM_STATU
{
	DROP,
	INVENTORY,
	WEAR,
};

class CItem : public CGameObject
{
	
	char m_cItemStatu;
	GROUP_ITEM m_eItemType;
public:
	CItem();
	~CItem();

	virtual void update();
	virtual void render();


	void SetDrop();
	void SetInventory();
	void SetWear();

	void SetStatu(UINT bit);
	bool GetStatu(UINT bit);
	void RemoveStatu(UINT bit);

	virtual void CreateItem() {};
	virtual void OnCollisionEnter(CCollider* pOther);
};
