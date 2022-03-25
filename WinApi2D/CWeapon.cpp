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
			m_sKey = L"Sword";																			//sword �ִϸ��̼� Key
			m_sAttackInfo->m_sEffKey		= m_sKey+L"Eff";											//Effect �ִϸ��̼� key  // Key�� null�̸� �Ǽ�
			m_sAttackInfo->m_fDelay			= 0.53f;													//���� ������
			m_sAttackInfo->m_fRange			= 100.f;													//���� ���� �÷��̾� �������� �ȼ� ������ 
			m_sAttackInfo->m_fVelocity		= 0.f;														//���Ÿ���� źȯ �̵��ӵ�
			m_sAttackInfo->m_fAniTime		= 0.05;														//�ִϸ��̼� �ӵ�
			m_sAttackInfo->m_iAniCut		= 6;														//�ִϸ��̼� ��������
			m_sAttackInfo->m_fDestroyTime = m_sAttackInfo->m_fAniTime * m_sAttackInfo->m_iAniCut;		//����Ʈ ���� ����?
			m_sAttackInfo->m_fAniScale		= fPoint(50, 50);											//�ִϸ��̼� ������
			m_sAttackInfo->m_fColScale		= fPoint(150, 150);											//���� �浹ü ũ��
			m_sAttackInfo->m_IsMultiple		= true;														//�� �ݶ��̴��� �ټ��� �������� , 
			m_sAttackInfo->m_eKind			= ITEM_KIND::SWORD;											//������ ���� â , �� , �� , DEFAULT �Ǽ� 
			m_eItemType						= ITEM_TYPE::ONE_HAND_WEAPON;								//�Ѽհ� �μհ� ������ Ŭ���Ҷ� ������ ����â
			m_sEffect;																					//ȿ�� ������ Ŭ���Ҷ� ������ ����â
			m_sExplanation;																				//ȿ�� ������ Ŭ���Ҷ� ������ ����â
			SetScale(fPoint(20, 20));																	//���� ũ��;
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



	/// �Ʒ���  �պ�����

	switch (m_sAttackInfo->m_eKind)
	{
	case ITEM_KIND::SWORD:
	case ITEM_KIND::SPEAR:
		m_sAttackInfo->m_IsMultiple = true; // �ѳ� �����ϴ� �������̸� ���� ����
		m_sAttackInfo->m_fVelocity = 0;
		break;
	}


	//TODO: �ؾ���
	switch (m_eItemType)
	{
	case ITEM_TYPE::ONE_HAND_WEAPON:
		m_sType = L"�Ѽհ�";
		break;
	case ITEM_TYPE::TWO_HAND_WEAPON:
		m_sType = L"�μհ�";
			break;
	case ITEM_TYPE::SUB_WEAPON:
		m_sType = L"��������";
			break;
	}


	//TODO: �ؾ���
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



	if (pOtherObj->GetName() == L"Tile") //TODO: ���߿� Ÿ�Ϸ� �ٲܰ�
	{
		SetStatu((UINT)ITEM_STATU::STAY);
	}
}

