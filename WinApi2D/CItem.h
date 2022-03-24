#pragma once
#include "CGameObject.h"

enum class ITEM_STATU
{
	DROP,
	STAY,
	INVENTORY,
	WEAR,
	NONE,
};

class CD2DImage;

class CItem : public CGameObject
{
protected:
	char m_cItemStatu;
	CD2DImage* m_pImg;
	wstring m_sKey;
	fPoint m_fDir;
	float m_fForce;

public:
	CItem();
	~CItem();

	virtual void update();
	virtual void render();


	virtual void ItemAniPlay() {};

	virtual CItem* Clone();
	void SetStay();
	void SetDrop();
	void SetInventory();
	void SetWear();

	void SetStatu(UINT bit);
	bool IsStatu(UINT bit);
	void RemoveStatu(UINT bit);


	virtual void CreateItem() {};
	virtual void OnCollisionEnter(CCollider* pOther);
};
