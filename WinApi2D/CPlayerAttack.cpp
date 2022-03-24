#include "framework.h"
#include "CPlayerAttack.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CAnimator.h"
#include "CWeapon.h"


CPlayerAttack* CPlayerAttack::Clone()
{

	CPlayerAttack* newAttack = new CPlayerAttack;

	newAttack->SetDir(this->m_fvDir);
	newAttack->SetPos(this->GetPos());
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


	return newAttack;
}

CPlayerAttack::CPlayerAttack()
{
	m_fvDir = fPoint(0,0);
	m_pImg = nullptr;
	m_fDestroy = 0.f;
	m_pWeaponAttackInfo = nullptr;


	SetName(L"PlayerAttack");
	CreateCollider();
	GetCollider()->SetScale(fPoint(200.f, 200.f));

	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SwordEff", L"texture\\Item\\SwordEff.png");
	GetAnimator()->CreateAnimation(L"SwordEff", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.05f, 6);
	GetAnimator()->Play(L"SwordEff");
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

	m_pImg = CResourceManager::getInst()->LoadD2DImage(m_pWeaponAttackInfo->m_sEffKey, L"texture\\Item\\" + m_pWeaponAttackInfo->m_sEffKey + L".png");
	GetAnimator()->CreateAnimation(m_pWeaponAttackInfo->m_sEffKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.05f, 6);
	GetAnimator()->Play(m_pWeaponAttackInfo->m_sEffKey);
}

CPlayerAttack::~CPlayerAttack()
{
	delete m_pWeaponAttackInfo;
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
		DeleteObj(this);
	}
}

void CPlayerAttack::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
}