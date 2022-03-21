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
	fPoint objectRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos()); //ĳ���� ���� ��ġ�� ����� �ؼ� 
	fVec2 playDir = fVec2(mousePos.x - objectRenderPos.x, mousePos.y - objectRenderPos.y); // ���콺�� ĳ������ ����
	GetStatu()->SetLook(playDir);
	

	// ĳ���� Ű�Է¿� ���� ���� ����
	if (KeyDown(VK_RBUTTON) && !StatuGet(GROUP_OBJECT_STATU::FORCE) && m_cDashCount < 100) // �뽬 ���� //TODO: �뽬 ���� m_cDashCount > 0�ؾ���
	{
		GetStatu()->SetForceDir(playDir); //�뽬 �̵� ������ ���ؾ���
		GetStatu()->SetForce(DASHVELOCITY);
		StatuSet(GROUP_OBJECT_STATU::FORCE);
		m_cDashCount -= 1;
	}
	else if (StatuGet(GROUP_OBJECT_STATU::FORCE)) //�뽬��
	{
		m_fDashTime += fDT;
		StatuSet(GROUP_OBJECT_STATU::GROUND);
		if (StatuGet(GROUP_OBJECT_STATU::JUMP)) //�����ϰ� �뽬�� ����ϸ� 
		{
			StatuRemove(GROUP_OBJECT_STATU::JUMP); //������ ���� �����ָ� RigidBody�� �����Լ��� ��� �����Ͽ� �̻��ϰ� �����
		}
		if (m_fDashTime > DASHTIME) 
		{
			m_fDashTime = 0;
			StatuRemove(GROUP_OBJECT_STATU::FORCE);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}

	}
	else //�뽬���̸� ����Ű �ȵ�
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

		if (KeyDown(VK_SPACE)   // ����
			&& !StatuGet(GROUP_OBJECT_STATU::JUMP)
			&& StatuGet(GROUP_OBJECT_STATU::GROUND))
		{
			StatuSet(GROUP_OBJECT_STATU::JUMP);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}
		if (KeyDown(VK_RBUTTON) && !StatuGet(GROUP_OBJECT_STATU::ATTACK) ) //����
		{
			StatuSet(GROUP_OBJECT_STATU::ATTACK);
			//CreateObj(PlayerAttack(),GROUP_GAMEOBJ::PLAYER_ATTACK);
		}

	}
	SetPos(pos);


	StatuSet(GROUP_OBJECT_STATU::GROUND); //TODO: ���߿� �����
	// ĳ���� ���¿� ���� �ִϸ��̼�
	StatuAnimator();

	//Statu ������Ʈ �߷�, �뽬 ����
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

	
	if (pOtherObj->GetName() == L"Monster") //TODO: ���߿� Ÿ�Ϸ� �ٲܰ�
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