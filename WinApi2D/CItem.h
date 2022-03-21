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

class CD2DImage;

class CItem : public CGameObject
{
	
	char m_cItemStatu;
	GROUP_ITEM m_eItemType;
	CD2DImage* m_pImg;
public:
	CItem();
	~CItem();

	virtual void update();
	virtual void render();


	virtual void DropUpdate() {};
	virtual void InventoryUpdate() {};
	virtual void WearUpdate() {};
	
	virtual void DropRender() {};
	virtual void InventoryRender() {};
	virtual void WearRender() {};



	void SetDrop();
	void SetInventory();
	void SetWear();

	void SetStatu(UINT bit);
	bool IsStatu(UINT bit);
	void RemoveStatu(UINT bit);

	void RoadItemResource();

	virtual void CreateItem() {};
	virtual void OnCollisionEnter(CCollider* pOther);
};
