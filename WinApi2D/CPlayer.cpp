#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"



#define DASHCREATETIME 1.2f
#define DASHVELOCITY 1000.f
#define DASHTIME 0.25f

CPlayer::CPlayer()
{
	m_iPlayerStatu = 0;
	m_fVelocity = 500;
	m_cDashCount = 2;
	m_cMaxDashCount = 2;
	m_fDashTime = 0;
	m_fDashDir = fVec2(0.f, 0.f);
	SetScale(fPoint(70.f, 70.f));
	SetName(L"Player");

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Animation_Player.bmp");


	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"LeftNone", m_pImg, fPoint(0.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"RightNone", m_pImg, fPoint(0.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"LeftMove", m_pImg, fPoint(0.f, 140.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"RightMove", m_pImg, fPoint(0.f, 210.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 3);
	GetAnimator()->CreateAnimation(L"LeftHit", m_pImg, fPoint(140.f, 0.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
	GetAnimator()->CreateAnimation(L"RightHit", m_pImg, fPoint(140.f, 70.f), fPoint(70.f, 70.f), fPoint(70.f, 0.f), 0.25f, 1);
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

	if (m_cDashCount < m_cMaxDashCount)
	{
		m_fCreateDashTime += fDT;
		if (m_fCreateDashTime >= DASHCREATETIME)
		{
			m_cDashCount += 1;
			m_fCreateDashTime -= DASHCREATETIME;
		}
	}
	

	if (KeyDown(VK_RBUTTON) && !StatuGet(GROUP_OBJECT_STATU::DASH) && m_cDashCount > 0) // 대쉬 진입
	{

		fVec2 mousePos = MousePos(); //마우스의 현재 좌표와
		fPoint objectRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos()); //캐릭터 랜더 위치랑 계산을 해서 

		GetRigidBody()->SetDashDir(fVec2(mousePos.x - objectRenderPos.x , mousePos.y - objectRenderPos.y)); //대쉬 이동 방향을 정해야함
		GetRigidBody()->SetVelocity(DASHVELOCITY);
		StatuSet(GROUP_OBJECT_STATU::DASH);
		//StatuSet(GROUP_OBJECT_STATU::GROUND);
		m_cDashCount -= 1;
	}
	else if (StatuGet(GROUP_OBJECT_STATU::DASH)) //대쉬중
	{
		m_fDashTime += fDT;
		if (m_fDashTime > DASHTIME)
		{
			m_fDashTime = 0;
			StatuRemove(GROUP_OBJECT_STATU::DASH);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}
	}
	else //대쉬중이면 이동안됨 
	{
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

		if (KeyDown(VK_SPACE)   // 점프
			&& !StatuGet(GROUP_OBJECT_STATU::JUMP)
			&& StatuGet(GROUP_OBJECT_STATU::GROUND))
		{
			StatuSet(GROUP_OBJECT_STATU::JUMP);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}
	}

	if (KeyDown('Q')) //TODO: 바닥 충돌 바닥과 충돌되었다고 가정 나중에 삭제
	{
		StatuRemove(GROUP_OBJECT_STATU::JUMP);
		StatuSet(GROUP_OBJECT_STATU::GROUND);
	}
	SetPos(pos);

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
	if (pOtherObj->GetName() == L"Monster") //TODO: 나중에 타일로 바꿀것
	{
		StatuSet(GROUP_OBJECT_STATU::GROUND);
		StatuRemove(GROUP_OBJECT_STATU::JUMP);
	}
}