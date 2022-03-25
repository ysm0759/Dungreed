#include "framework.h"
#include "CWeapon.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"
#include "CPlayer.h"

CWeapon::CWeapon()
{
	m_sAttackInfo = nullptr;

}


CWeapon* CWeapon::Clone()
{
	return new CWeapon(*this);
}
CWeapon::CWeapon(ITEM_STATU itemStatu , WEAPON_KIND weaponKind , fPoint pos)
{

	SetPos(pos);
	SetName(L"Weapon");
	m_sAttackInfo = new WeaponAttackInfo();
	switch (weaponKind)
	{
		case WEAPON_KIND::DEFAULT_SWORD:
			m_sKey = L"Sword";																			//sword 애니메이션 Key
			m_sAttackInfo->m_sEffKey		= m_sKey+L"Eff";											//Effect 애니메이션 key  // Key가 null이면 맨손
			m_sAttackInfo->m_fDelay			= 0.53f;													//공격 딜레이
			m_sAttackInfo->m_fRange			= 100.f;													//공격 범위 플레이어 기준으로 픽셀 원단위 
			m_sAttackInfo->m_fVelocity		= 0.f;														//원거리라면 탄환 이동속도
			m_sAttackInfo->m_fAniTime		= 0.05;														//애니메이션 속도
			m_sAttackInfo->m_iAniCut		= 6;														//애니메이션 몇컷인지
			m_sAttackInfo->m_fDestroyTime = m_sAttackInfo->m_fAniTime * m_sAttackInfo->m_iAniCut;		//임펙트 몇초 유지?
			m_sAttackInfo->m_fAniScale		= fPoint(50, 50);											//애니메이션 스케일
			m_sAttackInfo->m_fColScale		= fPoint(150, 150);											//공격 충돌체 크기
			m_sAttackInfo->m_IsMultiple		= true;														//한 콜라이더가 다수를 때리는지 , 
			m_sAttackInfo->m_eKind			= ITEM_KIND::SWORD;											//아이템 종류 창 , 검 , 총 , DEFAULT 맨손 
			m_eItemType						= ITEM_TYPE::ONE_HAND_WEAPON;								//한손검 두손검 아이템 클릭할때 나오는 정보창
			m_sEffect;																					//효과 아이템 클릭할때 나오는 정보창
			m_sExplanation;																				//효과 아이템 클릭할때 나오는 설명창
			SetScale(fPoint(20, 20));																	//무기 크기;
			//SetEquipmentItemStat();
			break;
		case WEAPON_KIND::DEFAULT_GUN:
			m_sKey = L"Gun";
			m_sAttackInfo->m_sEffKey = m_sKey + L"Eff";
			m_sAttackInfo->m_fDelay = 0.53f;
			m_sAttackInfo->m_fRange = 20.f;
			m_sAttackInfo->m_fVelocity = 200.f;
			m_sAttackInfo->m_fAniTime = 0.05;
			m_sAttackInfo->m_iAniCut = 4;
			m_sAttackInfo->m_fDestroyTime = m_sAttackInfo->m_fAniTime * m_sAttackInfo->m_iAniCut + 30.f;
			m_sAttackInfo->m_fAniScale = fPoint(10, 20);
			m_sAttackInfo->m_fColScale = fPoint(10, 20);
			m_sAttackInfo->m_IsMultiple = true;
			m_sAttackInfo->m_eKind = ITEM_KIND::GUN;
			m_eItemType = ITEM_TYPE::TWO_HAND_WEAPON;
			m_sEffect;
			m_sExplanation;
			SetScale(fPoint(20, 20));
			break;

	}



	/// 아래쪽  손봐야함

	switch (m_sAttackInfo->m_eKind)
	{
	case ITEM_KIND::SWORD:
	case ITEM_KIND::SPEAR:
		m_sAttackInfo->m_IsMultiple = true; // 한놈씩 공격하는 아이템이면 따로 지정
		m_sAttackInfo->m_fVelocity = 0;
		break;
	}


	//TODO: 해야함
	switch (m_eItemType)
	{
	case ITEM_TYPE::ONE_HAND_WEAPON:
		m_sType = L"한손검";
		break;
	case ITEM_TYPE::TWO_HAND_WEAPON:
		m_sType = L"두손검";
			break;
	case ITEM_TYPE::SUB_WEAPON:
		m_sType = L"보조무기";
			break;
	}


	//TODO: 해야함
	switch (itemStatu)
	{
	case ITEM_STATU::DROP:
		CreateCollider();
		GetCollider()->SetScale(GetScale()+fPoint(10,40));
		SetDrop();
		break;
	case ITEM_STATU::INVENTORY:
		SetInventory();
		break;
	case ITEM_STATU::WEAR:
		SetWear();
		break;
	case ITEM_STATU::NONE:
		break;
	}




	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");
	GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 1);
	GetAnimator()->Play(m_sKey);
}

CWeapon::~CWeapon()
{
	if (nullptr != m_sAttackInfo)
	{
		delete m_sAttackInfo;
	}

}




WeaponAttackInfo* CWeapon::GetInfo()
{
	return m_sAttackInfo;
}


void CWeapon::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();



	if (pOtherObj->GetName() == L"Player")
	{
		if (IsStatu((UINT)ITEM_STATU::DROP))
		{
			if (((CPlayer*)pOtherObj)->GetCurItem(ITEM_PART::LeftWeapon) == nullptr)
			{
				CItem* tmp = ((CPlayer*)pOtherObj)->GetCurItem(ITEM_PART::LeftWeapon);
				tmp = this;
			}
		}
	}



	if (pOtherObj->GetName() == L"Tile") //TODO: 나중에 타일로 바꿀것
	{
		SetStatu((UINT)ITEM_STATU::STAY);
	}
}

