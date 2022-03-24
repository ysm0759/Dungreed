#pragma once


#include "CEquipment.h"

enum class ITEM_KIND
{
	DEFAULT,
	SWORD,
	SPEAR,
	GUN,
	SIZE,
};

enum class WEAPON_KIND
{


	DEFAULT_SWORD,




	DEFAULT_SPEAR,
	
	
	DEFAULT_GUN,



	SIZE,
};

struct WeaponAttackInfo
{
	float m_fDelay;	     //���� ������
	float m_fRange;		 //���� ���� �÷��̾� �������� �ȼ� ������ 
	float m_fVelocity;	 //���Ÿ���� źȯ �̵��ӵ�
	float m_fDestroyTime; //����Ʈ ���� ����?

	wstring m_sWeaponKey; //sword �ִϸ��̼� Key
	wstring m_sEffKey;	 //Effect �ִϸ��̼� key  // Key�� null�̸� �Ǽ�
	

	fPoint m_fAniScale;   //�ִϸ��̼� ������
	fPoint m_fColScale;  //���� �浹ü ũ��

	bool m_IsMultiple;   //�� �ݶ��̴��� �ټ��� �������� , 
	ITEM_KIND m_eKind;   //������ ���� â , �� , �� , DEFAULT �Ǽ� �Ǽ�
};


class CWeapon : public CEquipment
{
	WeaponAttackInfo m_sAttackInfo;

public:
	CWeapon();
	CWeapon(ITEM_STATU itemStatu, WEAPON_KIND weaponKind , fPoint pos);
	~CWeapon();
	void SetWeaponDelay(float delay);
	void SetWeaponRange(float range);
	void SetWeaponColScale(fPoint colScale);
	void SetWeaponKey(wstring key);
	void SetWeaponKind(ITEM_KIND kind);	
	void SetWeaponMultiple(bool multiple);
	void SetWeaponVelocity(float velocity);
	void SetWeaponDestroyTime(float destroyTime);
	void SetWeaponAniScale(fPoint aniScale);
	WeaponAttackInfo* GetInfo();

};

