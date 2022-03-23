#include "framework.h"
#include "CPlayerAttack.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CAnimator.h"
#include "CWeapon.h"


CPlayerAttack* CPlayerAttack::Clone()
{
	return new CPlayerAttack(*this);
}

CPlayerAttack::CPlayerAttack()
{
	m_pWeaponAttackInfo = new WeaponAttackInfo();
	m_fvDir = fVec2(0, -1); // 잘못설정하면 위로 날라감
	m_fDestroy = 0.f;
	m_pWeaponAttackInfo->m_fAniScale = {};
	m_pWeaponAttackInfo->m_fRange = 100.f;
	m_pWeaponAttackInfo->m_fDestroyTime = 0.6f;
	SetName(L"PlayerAttack");
	CreateCollider();
	GetCollider()->SetScale(fPoint(200.f, 200.f));

	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SwordEff", L"texture\\Item\\SwordEff.png");
	GetAnimator()->CreateAnimation(L"SwordEff", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.05f, 6);
}

CPlayerAttack::CPlayerAttack(CWeapon* pCurentWeapon)
{


	m_pWeaponAttackInfo = pCurentWeapon->GetInfo();
	m_fvDir = fVec2(0, -1); // 잘못설정하면 위로 날라감
	m_fDestroy = 0.f;


	SetName(L"PlayerAttack");
	CreateCollider();
	GetCollider()->SetScale(m_pWeaponAttackInfo->m_fColScale);

	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(m_pWeaponAttackInfo->m_sEffKey, L"texture\\Item\\SwordEff.png");
	GetAnimator()->CreateAnimation(L"SwordEff", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.05f, 6);
}

CPlayerAttack::~CPlayerAttack()
{
	if (nullptr != m_pWeaponAttackInfo)
	{
		delete m_pWeaponAttackInfo;
	}
}

void CPlayerAttack::update()
{
	
	//pos.x += m_fVelocity * m_fvDir.x * fDT;
	//pos.y += m_fVelocity * m_fvDir.y * fDT;

	//SetPos(pos);

	if (m_fDestroy >= m_pWeaponAttackInfo->m_fDestroyTime)
	{
		DeleteObj(this);
	}
	m_fDestroy += fDT;
	GetAnimator()->update();
}

void CPlayerAttack::render()
{
	fPoint pos = fPoint(m_pWeaponAttackInfo->m_fRange *GetPos().x, m_pWeaponAttackInfo->m_fRange * GetPos().y);
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);


	GetAnimator()->Play(m_pWeaponAttackInfo->m_sEffKey, m_pWeaponAttackInfo->m_fAniScale);
	component_render();

}


void CPlayerAttack::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
	fPoint pos = fPoint(m_pWeaponAttackInfo->m_fRange * m_fvDir.normalize().x + GetPos().x,
						m_pWeaponAttackInfo->m_fRange * m_fvDir.normalize().y + GetPos().y);
	SetPos(pos);
}


void CPlayerAttack::SetDir(float theta)
{
	m_fvDir.x = (float)cos(theta);
	m_fvDir.y = (float)sin(theta);
}


void CPlayerAttack::SetColSize(fPoint size)
{
	GetCollider()->SetScale(size);
}


void CPlayerAttack::SetAniSize(fPoint size)
{
	this->m_pWeaponAttackInfo->m_fAniScale = size;
}

void CPlayerAttack::SetKey(wstring key)
{
	this->m_pWeaponAttackInfo->m_sEffKey = key;
}

void CPlayerAttack::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}
