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
	float m_fDelay;	     //공격 딜레이
	float m_fRange;		 //공격 범위 플레이어 기준으로 픽셀 원단위 
	float m_fVelocity;	 //원거리라면 탄환 이동속도
	float m_fDestroyTime; //임펙트 몇초 유지?

	wstring m_sWeaponKey; //sword 애니메이션 Key
	wstring m_sEffKey;	 //Effect 애니메이션 key  // Key가 null이면 맨손
	

	fPoint m_fAniScale;   //애니메이션 스케일
	fPoint m_fColScale;  //공격 충돌체 크기

	bool m_IsMultiple;   //한 콜라이더가 다수를 때리는지 , 
	ITEM_KIND m_eKind;   //아이템 종류 창 , 검 , 총 , DEFAULT 맨손 맨손
};


class CWeapon : public CEquipment
{
	WeaponAttackInfo* m_sAttackInfo;

public:
	CWeapon();
	CWeapon(ITEM_STATU itemStatu, WEAPON_KIND weaponKind , fPoint pos);
	~CWeapon();

	virtual CWeapon* Clone();
	WeaponAttackInfo* GetInfo();

};

