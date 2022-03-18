#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CStatu.h"



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

	

	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));


	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerImg", L"texture\\Player\\PlayerStand.png");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 5);
	GetAnimator()->Play(L"PlayerStand");

	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\Player\\PlayerRun.png");
	GetAnimator()->CreateAnimation(L"PlayerRun", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7);
	GetAnimator()->Play(L"PlayerRun");
	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\Player\\PlayerJump.png");
	GetAnimator()->CreateAnimation(L"PlayerJump", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 1);
	GetAnimator()->Play(L"PlayerJump");



	CreateStatu();

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

	//대쉬 초기화
	if (m_cDashCount < m_cMaxDashCount)
	{
		m_fCreateDashTime += fDT;
		if (m_fCreateDashTime >= DASHCREATETIME)
		{
			m_cDashCount += 1;
			m_fCreateDashTime -= DASHCREATETIME;
		}
	}
	

	// 캐릭터 키입력에 따른 상태 변경
	if (KeyDown(VK_RBUTTON) && !StatuGet(GROUP_OBJECT_STATU::FORCE) && m_cDashCount < 100) // 대쉬 진입 //TODO: 대쉬 삭제 m_cDashCount > 0해야함
	{

		fVec2 mousePos = MousePos(); //마우스의 현재 좌표와
		fPoint objectRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos()); //캐릭터 랜더 위치랑 계산을 해서 
		GetStatu()->SetDashDir(fVec2(mousePos.x - objectRenderPos.x , mousePos.y - objectRenderPos.y)); //대쉬 이동 방향을 정해야함
		GetStatu()->SetForce(DASHVELOCITY);
		StatuSet(GROUP_OBJECT_STATU::FORCE);
		m_cDashCount -= 1;
	}
	else if (StatuGet(GROUP_OBJECT_STATU::FORCE)) //대쉬중
	{
		m_fDashTime += fDT;
		StatuSet(GROUP_OBJECT_STATU::GROUND);
		if (StatuGet(GROUP_OBJECT_STATU::JUMP)) //점프하고 대쉬를 사용하면 
		{
			StatuRemove(GROUP_OBJECT_STATU::JUMP); //점프를 제거 안해주면 RigidBody에 점프함수를 계속 실행하여 이상하게 진행됨
		}
		if (m_fDashTime > DASHTIME)
		{
			m_fDashTime = 0;
			StatuRemove(GROUP_OBJECT_STATU::FORCE);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}

	}
	else //대쉬중이면 조작키 안됨
	{
		if (Key(VK_LEFT))
		{
			pos.x -= m_fVelocity * fDT;
			StatuSet(GROUP_OBJECT_STATU::MOVE);
		}
		if (Key(VK_RIGHT))
		{
			pos.x += m_fVelocity * fDT;
			StatuSet(GROUP_OBJECT_STATU::MOVE);
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
	SetPos(pos);



	// 캐릭터 상태에 따른 애니메이션
	if (!StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerStand");
	}
	if(StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerRun");
	}
	if (!StatuGet(GROUP_OBJECT_STATU::GROUND) && StatuGet(GROUP_OBJECT_STATU::JUMP) || StatuGet(GROUP_OBJECT_STATU::FORCE))
	{
		GetAnimator()->Play(L"PlayerJump");
	}


	StatuRemove(GROUP_OBJECT_STATU::MOVE);
	GetStatu()->update();
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

	CreateObj(pMissile, GROUP_GAMEOBJ::PLAYER_MISSILE);
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