#include "framework.h"
#include "CPlayerAttack.h"
#include "CCollider.h"
#include "CStatu.h"
#include "CAnimator.h"
CPlayerAttack* CPlayerAttack::Clone()
{
	return new CPlayerAttack(*this);
}

CPlayerAttack::CPlayerAttack()
{
	m_fvDir = fVec2(-1, -1);
	m_fAniScale = {};
	m_fDestroyTime = 0.6f;
	m_fDestroy = 0.f;
	m_fRange = 100.f;
	SetName(L"PlayerAttack");
	CreateCollider();
	GetCollider()->SetScale(fPoint(200.f, 200.f));

	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"SwordEff", L"texture\\Item\\SwordEff.png");
	GetAnimator()->CreateAnimation(L"SwordEff", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 6);
	
}

CPlayerAttack::~CPlayerAttack()
{

}

void CPlayerAttack::update()
{
	
	//pos.x += m_fVelocity * m_fvDir.x * fDT;
	//pos.y += m_fVelocity * m_fvDir.y * fDT;

	//SetPos(pos);

	if (m_fDestroy >= m_fDestroyTime)
	{
		DeleteObj(this);
	}
	m_fDestroy += fDT;
	GetAnimator()->update();
}

void CPlayerAttack::render()
{
	fPoint pos = fPoint(m_fRange *GetPos().x, m_fRange * GetPos().y);
	fPoint scale = GetScale();

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(pos);


	GetAnimator()->Play(m_sKey, m_fAniScale);
	component_render();

}


void CPlayerAttack::SetDir(fVec2 vec)
{
	m_fvDir = vec.normalize();
	fPoint pos = fPoint(m_fRange * m_fvDir.normalize().x + GetPos().x, m_fRange * m_fvDir.normalize().y + GetPos().y);
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
	this->m_fAniScale = size;
}

void CPlayerAttack::SetKey(wstring key)
{
	this->m_sKey = key;
}

void CPlayerAttack::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObj(this);
	}
}
