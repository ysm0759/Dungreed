#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

 




CPlayer::CPlayer()
{
	m_iPlayerStatu = 0;
	m_fVelocity = 500;
	m_cDashCount = 2;
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation_Player.bmp");
	SetName(L"Player");
	SetScale(fPoint(70.f, 70.f));

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"LeftNone",		m_pImg, fPoint(0.f, 0.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"RightNone",	m_pImg, fPoint(0.f, 70.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"LeftMove",		m_pImg, fPoint(0.f, 140.f),	fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RightMove",	m_pImg, fPoint(0.f, 210.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"LeftHit",		m_pImg, fPoint(140.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit",		m_pImg, fPoint(140.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->Play(L"LeftNone");

	CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);

	CreateRigidBody();

}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::update()
{
	fPoint pos = GetPos();

	if (Key(VK_LEFT))
	{
		pos.x -= m_fVelocity * fDT;
		GetAnimator()->Play(L"LeftMove");
	}
	if (Key(VK_RIGHT))
	{
		pos.x += m_fVelocity * fDT;
		GetAnimator()->Play(L"RightMove");
	}				   
	if (Key(VK_UP))	   
	{				   
		pos.y -= m_fVelocity * fDT;
	}				   
	if (Key(VK_DOWN))  
	{				   
		pos.y += m_fVelocity * fDT;
	}
	if (Key(VK_RBUTTON))
	{
		StatuSet(GROUP_OBJECT_STATU::DASH);
		StatuRemove(GROUP_OBJECT_STATU::GROUND);
	}
	SetPos(pos);
 	if (KeyDown(VK_SPACE)  
		&& !StatuGet(GROUP_OBJECT_STATU::JUMP)
		&& StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		StatuSet(GROUP_OBJECT_STATU::JUMP);
		StatuRemove(GROUP_OBJECT_STATU::GROUND);
	}
	if (KeyDown('Q')) //TODO 바닥 충돌 바닥과 충돌되었다고 가정
	{
		StatuRemove(GROUP_OBJECT_STATU::JUMP);
		StatuSet(GROUP_OBJECT_STATU::GROUND);
	}


	GetRigidBody()->update();
	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::CreateMissile()
{
 	fPoint fpMissilePos = GetPos();
	fpMissilePos.x += GetScale().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetPos(fpMissilePos);
	pMissile->SetDir(fVec2(1, 0));

	CreateObj(pMissile, GROUP_GAMEOBJ::MISSILE_PLAYER);
}


void CPlayer::OnCollisionEnter(CCollider* pOther)
{

	CGameObject* pOtherObj = pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster") //TODO :: 나중에 타일로 바꿀것
	{	
		StatuSet(GROUP_OBJECT_STATU::GROUND);
		StatuRemove(GROUP_OBJECT_STATU::JUMP);
	}
}