#include "framework.h"
#include "CAttack.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CCoin.h"
#include "CD2DImage.h"
#include "CStatu.h"

CAttack::CAttack()
{
	m_eType = GROUP_ATTACK_TYPE::NONE;
	m_pImg = nullptr;
	m_fColliderSize = {};
	m_fImgSize = {};
	CreateCollider();
	CreateAnimator();
}

CAttack::~CAttack()
{

}


CAttack* CAttack::Clone()
{
	return new CAttack(*this);
}

void CAttack::MakeAttack(GROUP_ATTACK_TYPE atkType , fPoint colliderSize, fPoint imgSize , wstring key)
{
	m_eType = atkType;

	if (GROUP_ATTACK_TYPE::NONE == m_eType) 
	{
		assert(nullptr);
	}
	this->m_sKey = key;
	CreateCollider();
	CreateAnimator();
	GetCollider()->SetScale(colliderSize);
}

void CAttack::PlayerAttack()
{
	CAttack* attackClone = this->Clone();
	CreateObj(attackClone, GROUP_GAMEOBJ::PLAYER_ATTACK);
}

void CAttack::update()
{
	// 업데이트 상황에 따라 다르게 총이랑 근접무기 
	GetAnimator()->update();
}

void CAttack::render()
{
	GetAnimator()->Play(m_sKey, m_fImgSize);
	component_render();
}

void CAttack::OnCollisionEnter(CCollider* pOther)
{

	CGameObject* pOtherObj = pOther->GetObj();

	if (m_eType == GROUP_ATTACK_TYPE::WEAPON)
	{

	}
	else if (m_eType == GROUP_ATTACK_TYPE::SPEAR)
	{

	}
	else if (m_eType == GROUP_ATTACK_TYPE::GUN)
	{
		
	}
	else
	{
		assert(nullptr);
	}
}