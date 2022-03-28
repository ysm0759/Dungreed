#include "framework.h"
#include "CPlayerAttack.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CAnimator.h"
#include "CWeapon.h"


CPlayerAttack* CPlayerAttack::Clone()
{

	CPlayerAttack* newAttack = new CPlayerAttack;

	newAttack->m_pWeaponAttackInfo = new WeaponAttackInfo();
	newAttack->m_pWeaponAttackInfo->m_eKind = m_pWeaponAttackInfo->m_eKind;
	newAttack->m_pWeaponAttackInfo->m_fDelay = m_pWeaponAttackInfo->m_fDelay;
	newAttack->m_pWeaponAttackInfo->m_fAniScale = m_pWeaponAttackInfo->m_fAniScale;
	newAttack->m_pWeaponAttackInfo->m_fColScale = m_pWeaponAttackInfo->m_fColScale;
	newAttack->m_pWeaponAttackInfo->m_fDestroyTime = m_pWeaponAttackInfo->m_fDestroyTime;
	newAttack->m_pWeaponAttackInfo->m_fRange = m_pWeaponAttackInfo->m_fRange;
	newAttack->m_pWeaponAttackInfo->m_fVelocity = m_pWeaponAttackInfo->m_fVelocity;
	newAttack->m_pWeaponAttackInfo->m_IsMultiple = m_pWeaponAttackInfo->m_IsMultiple;
	newAttack->m_pWeaponAttackInfo->m_sEffKey = m_pWeaponAttackInfo->m_sEffKey;
	newAttack->m_pWeaponAttackInfo->m_sWeaponKey = m_pWeaponAttackInfo->m_sWeaponKey;
	newAttack->m_pWeaponAttackInfo->m_iAniCut = m_pWeaponAttackInfo->m_iAniCut;
	newAttack->m_pWeaponAttackInfo->m_fAniTime = m_pWeaponAttackInfo->m_fAniTime;
	newAttack->SetPos(this->GetPos());
	newAttack->SetDir(this->m_fvDir);
	newAttack->SetName(L"PlayerAttack");
	newAttack->CreateCollider();
	newAttack->GetCollider()->SetScale(m_pWeaponAttackInfo->m_fColScale);
	newAttack->CreateAnimator();

	newAttack->m_pImg = CResourceManager::getInst()->LoadD2DImage(m_pWeaponAttackInfo->m_sEffKey,
																	L"texture\\Item\\" + m_pWeaponAttackInfo->m_sEffKey + L".png");
	
\

	newAttack->GetAnimator()->CreateAnimation(m_pWeaponAttackInfo->m_sEffKey, m_pImg,
									fPoint(0, 0),
									fPoint(m_pWeaponAttackInfo->m_fAniSize.x, m_pWeaponAttackInfo->m_fAniSize.y),
									fPoint(m_pWeaponAttackInfo->m_fAniSize.x, 0),
									m_pWeaponAttackInfo->m_fAniTime,
									m_pWeaponAttackInfo->m_iAniCut);

	newAttack->GetAnimator()->Play(m_pWeaponAttackInfo->m_sEffKey);
	return newAttack;
}

CPlayerAttack::CPlayerAttack()
{
	m_fvDir = fPoint(0,0);
	m_pImg = nullptr;
	m_fDestroy = 0.f;
	m_pWeaponAttackInfo = nullptr;

}

CPlayerAttack::CPlayerAttack(CWeapon* pCurentWeapon)
{


	m_pWeaponAttackInfo = new WeaponAttackInfo();
	m_pWeaponAttackInfo->m_eKind = pCurentWeapon->GetInfo()->m_eKind;
	m_pWeaponAttackInfo->m_fDelay = pCurentWeapon->GetInfo()->m_fDelay;
	m_pWeaponAttackInfo->m_fAniScale = pCurentWeapon->GetInfo()->m_fAniScale;
	m_pWeaponAttackInfo->m_fColScale = pCurentWeapon->GetInfo()->m_fColScale;
	m_pWeaponAttackInfo->m_fDestroyTime = pCurentWeapon->GetInfo()->m_fDestroyTime;
	m_pWeaponAttackInfo->m_fRange = pCurentWeapon->GetInfo()->m_fRange;
	m_pWeaponAttackInfo->m_fVelocity = pCurentWeapon->GetInfo()->m_fVelocity;
	m_pWeaponAttackInfo->m_IsMultiple = pCurentWeapon->GetInfo()->m_IsMultiple;
	m_pWeaponAttackInfo->m_sEffKey = pCurentWeapon->GetInfo()->m_sEffKey;
	m_pWeaponAttackInfo->m_sWeaponKey = pCurentWeapon->GetInfo()->m_sWeaponKey;
	m_pWeaponAttackInfo->m_iAniCut = pCurentWeapon->GetInfo()->m_iAniCut;
	m_pWeaponAttackInfo->m_fAniTime = pCurentWeapon->GetInfo()->m_fAniTime;
	m_pWeaponAttackInfo->m_fAniSize = pCurentWeapon->GetInfo()->m_fAniSize;
	//	pCurentWeapon->GetInfo();
	
	m_fvDir = fVec2(0, -1); // 잘못설정하면 위로 날라감
	m_fDestroy = 0.f;


	SetName(L"PlayerAttack");
	CreateCollider();
	GetCollider()->SetScale(m_pWeaponAttackInfo->m_fColScale);

	CreateAnimator();

	m_pImg = CResourceManager::getInst()->LoadD2DImage(m_pWeaponAttackInfo->m_sEffKey, L"texture\\Item\\" + m_pWeaponAttackInfo->m_sEffKey + L".png");
	GetAnimator()->CreateAnimation(m_pWeaponAttackInfo->m_sEffKey, m_pImg, 
									fPoint(0, 0),
									fPoint(m_pWeaponAttackInfo->m_fAniSize.x, m_pWeaponAttackInfo->m_fAniSize.y),
									fPoint(m_pWeaponAttackInfo->m_fAniSize.x, 0),
									m_pWeaponAttackInfo->m_fAniTime,
									m_pWeaponAttackInfo->m_iAniCut);

	GetAnimator()->Play(m_pWeaponAttackInfo->m_sEffKey);
}

CPlayerAttack::~CPlayerAttack()
{

	delete m_pWeaponAttackInfo;

}

void CPlayerAttack::update()
{

	if (this->m_pWeaponAttackInfo->m_fVelocity >= 1.f )
	{

		fPoint pos = fPoint(GetPos());
		pos.x += m_pWeaponAttackInfo->m_fVelocity * m_fvDir.x * fDT;
		pos.y += m_pWeaponAttackInfo->m_fVelocity * m_fvDir.y * fDT;
		SetPos(pos);
	}

	if (m_fDestroy >= m_pWeaponAttackInfo->m_fDestroyTime)
	{
		DeleteObj(this);
	}
	m_fDestroy += fDT;
	GetAnimator()->update();
}

void CPlayerAttack::render()
{

	fPoint pos = fPoint(m_pWeaponAttackInfo->m_fRange * GetPos().x, m_pWeaponAttackInfo->m_fRange * GetPos().y);
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);

	GetAnimator()->Play(m_pWeaponAttackInfo->m_sEffKey, m_pWeaponAttackInfo->m_fAniScale);
	component_render();
}


void CPlayerAttack::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		//맞았을때 바로 사라지는 오브젝트
		if (this->m_pWeaponAttackInfo->m_IsMultiple)
		{

		}
		else
			DeleteObj(this);

	}
}

void CPlayerAttack::SetDir(fVec2 vec)
{
	this->m_fvDir = vec;
}

void CPlayerAttack::SetOffSetPos(fVec2 vec)
{
	m_fvDir = vec.normalize();
	fPoint pos = fPoint(m_pWeaponAttackInfo->m_fRange * m_fvDir.normalize().x + GetPos().x,
						m_pWeaponAttackInfo->m_fRange * m_fvDir.normalize().y + GetPos().y);
	SetPos(pos);
}