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
#define DASHVELOCITY 1500.f
#define DASHTIME 0.125f

CPlayer::CPlayer()
{
	m_fVelocity = 500;
	m_cDashCount = 2;
	m_cMaxDashCount = 2;
	m_fDashTime = 0;
	m_fDashDir = fVec2(0.f, 0.f);
	SetScale(fPoint(70.f, 70.f));
	SetName(L"Player");

	m_cPlayerInfo.AD = 0;
	m_cPlayerInfo.DF = 0;
	m_cPlayerInfo.Gold = 0;
	m_cPlayerInfo.HP = 0;
	m_cPlayerInfo.Satiety = 0;

	//m_cCurItem.Accessories = nullptr;
	m_cCurItem.LeftSubWeapon = nullptr;
	m_cCurItem.LeftWeapon = nullptr;
	m_cCurItem.RightSubWeapon = nullptr;
	m_cCurItem.RightWeapon = nullptr;


	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 60.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));



	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerStand", L"texture\\Player\\PlayerStand.png");
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 5);

	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\Player\\PlayerRun.png");
	GetAnimator()->CreateAnimation(L"PlayerRun", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7);

	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\Player\\PlayerJump.png");
	GetAnimator()->CreateAnimation(L"PlayerJump", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 1);

	//CAnimation* pAni;
	//pAni = GetAnimator()->FindAnimation(L"PlayerStand");
	//pAni->GetFrame(1).fptOffset = fPoint(-20.f, 0.f);
	
	
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
	fPoint mousePos = MousePos();
	fPoint objectRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos()); //캐릭터 랜더 위치랑 계산을 해서 
	fVec2 playDir = fVec2(mousePos.x - objectRenderPos.x, mousePos.y - objectRenderPos.y); // 마우스와 캐릭터의 방향
	GetStatu()->SetLook(playDir);
	

	// 캐릭터 키입력에 따른 상태 변경
	if (KeyDown(VK_RBUTTON) && !StatuGet(GROUP_OBJECT_STATU::FORCE) && m_cDashCount < 100) // 대쉬 진입 //TODO: 대쉬 삭제 m_cDashCount > 0해야함
	{
		GetStatu()->SetForceDir(playDir); //대쉬 이동 방향을 정해야함
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
		if (KeyDown(VK_RBUTTON) && !StatuGet(GROUP_OBJECT_STATU::ATTACK) ) //공격
		{
			StatuSet(GROUP_OBJECT_STATU::ATTACK);
			//CreateObj(PlayerAttack(),GROUP_GAMEOBJ::PLAYER_ATTACK);
		}

	}
	SetPos(pos);


	StatuSet(GROUP_OBJECT_STATU::GROUND); //TODO: 나중에 지울것
	// 캐릭터 상태에 따른 애니메이션
	StatuAnimator();

	//Statu 업데이트 중력, 대쉬 연산
	GetStatu()->update();

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}

void CPlayer::CreateAttack()
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

void CPlayer::StatuAnimator()
{
	if (!StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerStand", fPoint(50, 50), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	if (StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerRun", fPoint(50, 50), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	if (!StatuGet(GROUP_OBJECT_STATU::GROUND) || StatuGet(GROUP_OBJECT_STATU::JUMP) || StatuGet(GROUP_OBJECT_STATU::FORCE))
	{
		GetAnimator()->Play(L"PlayerJump", fPoint(50, 50), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	StatuRemove(GROUP_OBJECT_STATU::MOVE);

}

CGameObject* CPlayer::PlayerAttack()
{
	return nullptr;
}

void CPlayer::EatItem()
{

}