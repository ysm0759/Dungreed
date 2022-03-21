#pragma once

#include "CGameObject.h"

class CD2DImage;
class CItem;
class CWeapon;

struct ItemPart
{
	CItem* LeftWeapon;
	CItem* LeftSubWeapon;
	CItem* RightWeapon;
	CItem* RightSubWeapon;
	vector<CItem*> Accessories; //max 4
};

struct PlayerInfo
{
	int HP;
	int AD;
	int DF;
	int Satiety;
	int Gold;
	//스킬추가
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

	PlayerInfo m_cPlayerInfo;
	ItemPart m_cCurItem;
	list<CItem*> m_inventory;
	

	void CreateAttack();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();
	virtual void update();
	virtual void render();
	virtual void OnCollisionEnter(CCollider* pOther);
	void StatuAnimator();
	CGameObject* PlayerAttack();
	void EatItem();

};

