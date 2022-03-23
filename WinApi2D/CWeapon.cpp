#include "framework.h"
#include "CWeapon.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"
CWeapon::CWeapon()
{
	m_sAttackInfo.m_fDelay = 0.f;				  //���� ������
	m_sAttackInfo.m_fRange = 0.f;				  //���� ���� �÷��̾� �������� �ȼ� ������ 
	m_sAttackInfo.m_fVelocity = 0.f;			  //���Ÿ���� źȯ �̵��ӵ�
	m_sAttackInfo.m_fDestroyTime = 0.f;			  //����Ʈ ���� ����?
	m_sAttackInfo.m_sWeaponKey = L"";			  //sword �ִϸ��̼� Key
	m_sAttackInfo.m_sEffKey =L"";				  //Effect �ִϸ��̼� key  // Key�� null�̸� �Ǽ�
	m_sAttackInfo.m_fAniScale = {};				  //�ִϸ��̼� ������
	m_sAttackInfo.m_fColScale = {};				  //���� �浹ü ũ��
	m_sAttackInfo.m_IsMultiple = true;			  //�� �ݶ��̴��� �ټ��� �������� , 
	m_sAttackInfo.m_eKind = ITEM_KIND::DEFAULT;   //������ ���� â , �� , �� , DEFAULT �Ǽ� 
}

CWeapon::CWeapon(ITEM_STATU itemStatu , WEAPON_KIND weaponKind , fPoint pos)
{

	SetPos(pos);
	switch (weaponKind)
	{
		case WEAPON_KIND::DEFAULT_SWORD:
			m_sAttackInfo.m_fDelay			= 0.53f;							//���� ������
			m_sAttackInfo.m_fRange			= 100.f;							//���� ���� �÷��̾� �������� �ȼ� ������ 
			m_sAttackInfo.m_fVelocity		= 0;								//���Ÿ���� źȯ �̵��ӵ�
			m_sAttackInfo.m_fDestroyTime	= 0.6f;								//����Ʈ ���� ����?
			m_sAttackInfo.m_sWeaponKey		= L"Sword";							//sword �ִϸ��̼� Key
			m_sAttackInfo.m_sEffKey			= L"SwordEff";						//Effect �ִϸ��̼� key  // Key�� null�̸� �Ǽ�
			m_sAttackInfo.m_fAniScale		= fPoint(100, 100);					//�ִϸ��̼� ������
			m_sAttackInfo.m_fColScale		= fPoint(100, 100);					//���� �浹ü ũ��
			m_sAttackInfo.m_IsMultiple		= true;								//�� �ݶ��̴��� �ټ��� �������� , 
			m_sAttackInfo.m_eKind			= ITEM_KIND::SWORD;					//������ ���� â , �� , �� , DEFAULT �Ǽ� 
			m_eItemType						= ITEM_TYPE::ONE_HAND_WEAPON;		//�Ѽհ� �μհ� ������ Ŭ���Ҷ� ������ ����â
			m_sEffect;															//ȿ�� ������ Ŭ���Ҷ� ������ ����â
			m_sExplanation;														//ȿ�� ������ Ŭ���Ҷ� ������ ����â
			SetScale(fPoint(20, 20));											//���� ũ��;
			//SetEquipmentItemStat();
			break;

	}



	/// �Ʒ���  �պ�����

	switch (m_sAttackInfo.m_eKind)
	{
	case ITEM_KIND::SWORD:
	case ITEM_KIND::SPEAR:
		m_sAttackInfo.m_IsMultiple = true; // �ѳ� �����ϴ� �������̸� ���� ����
		m_sAttackInfo.m_fVelocity = 0;
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
		CreateStatu();
		StatuRemove(GROUP_OBJECT_STATU::GROUND);
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
	m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sAttackInfo.m_sWeaponKey, L"texture\\Item\\" + m_sAttackInfo.m_sWeaponKey + L".png");
	GetAnimator()->CreateAnimation(m_sAttackInfo.m_sWeaponKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 1);


}

CWeapon::~CWeapon()
{

}

void CWeapon::ItemAniPlay()
{
	this->GetAnimator()->Play(m_sAttackInfo.m_sWeaponKey, GetScale());
}



void CWeapon::SetWeaponDelay(float delay)
{
	m_sAttackInfo.m_fDelay = delay;
}

void CWeapon::SetWeaponRange(float range)
{
	m_sAttackInfo.m_fRange = range;
}

void CWeapon::SetWeaponColScale(fPoint colScale)
{
	m_sAttackInfo.m_fColScale = colScale;
}

void CWeapon::SetWeaponKey(wstring swordkey)
{
	m_sAttackInfo.m_sWeaponKey = swordkey;
	m_sAttackInfo.m_sEffKey = m_sAttackInfo.m_sWeaponKey + L"Eff";

}

void CWeapon::SetWeaponKind(ITEM_KIND kind)
{
	m_sAttackInfo.m_eKind = kind;
}

void CWeapon::SetWeaponMultiple(bool multiple)
{
}

void CWeapon::SetWeaponVelocity(float velocity)
{
	m_sAttackInfo.m_fVelocity = velocity;
}

void CWeapon::SetWeaponDestroyTime(float destroyTime)
{
	m_sAttackInfo.m_fDestroyTime = destroyTime;
}

void CWeapon::SetWeaponAniScale(fPoint aniScale)
{
	m_sAttackInfo.m_fAniScale = aniScale;
}

WeaponAttackInfo* CWeapon::GetInfo()
{
	return nullptr;
}

