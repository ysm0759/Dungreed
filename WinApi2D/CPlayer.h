#pragma once

#include "CGameObject.h"

class CD2DImage;
class CItem;
class CWeapon;
class CPlayerAttack;

enum class ITEM_PART
{
	LeftWeapon,
	LeftSubWeapon,
	RightWeapon,
	RightSubWeapon,
	ACCESSORIES1,
	ACCESSORIES2,
	ACCESSORIES3,
	ACCESSORIES4,
	SIZE,
};


struct PlayerInfo
{
	int HP;
	int AD;
	int DF;
	int Satiety;
	int Gold;
	//TODO: 스킬추가
};


class CPlayer : public CGameObject
{
private:


	CD2DImage* m_pImg;
	float m_fVelocity;
	fVec2 m_fDashDir;
	char m_cDashCount;
	char m_cMaxDashCount;
	float m_fCreateDashTime;
	float m_fDashTime;
	int m_iBottomCount;

	PlayerInfo m_cPlayerInfo;
	CItem* m_cCurItem[(UINT)ITEM_PART::SIZE];
	CGameObject* m_pCurWeapon;
	list<CItem*> m_inventory;

	CPlayerAttack* m_pPlayerAttack;


	void PlayerAttack(fPoint dir);
	void ItemSwap();
public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	virtual void update();
	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	virtual void OnCollisionExit(CCollider* pOther);
	void StatuAnimator();
	void EatItem();


	list<CItem*> GetInvetroy();
	CItem* GetCurItem(ITEM_PART type);
	void PrintInfo();
};

