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
	SIZE,
};

enum class ITEM_STATU
{
	DROP,
	INVENTORY,
	WEAR,
	NONE,
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


	virtual void DropUpdate() {};		// 아이템이 드랍 했을때 Update					
	virtual void DropRender() {};		// 아이템이 드랍 했을때 Render          



	virtual CItem* Clone();
	virtual void SetDrop();
	virtual void SetInventory();
	virtual void SetWear();

	void SetStatu(UINT bit);
	bool IsStatu(UINT bit);
	void RemoveStatu(UINT bit);


	void LoadItemResource();
	virtual void CreateItem() {};
	virtual void OnCollisionEnter(CCollider* pOther);
};
