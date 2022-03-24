#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CStatu.h"
#include "CGameItem.h"
#include "CPlayerAttack.h"
#include "CWeapon.h"
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
	m_pCurWeapon = nullptr;
	m_pPlayerAttack = nullptr;

	for (int i = 0; i < (UINT)ITEM_PART::SIZE; i++)
	{
		m_cCurItem[i] = nullptr;
	}

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

	CreateStatu();

	//���߿� �����
	this->m_pCurWeapon = new CWeapon(ITEM_STATU::DROP, WEAPON_KIND::DEFAULT_SWORD, GetPos());
	CreateObj(m_pCurWeapon, GROUP_GAMEOBJ::ITEM);
	//m_playerAttack = m_pCurWeapon;
	m_playerAttack = new CPlayerAttack((CWeapon*)m_pCurWeapon);
}

CPlayer::~CPlayer()
{
	delete m_playerAttack;
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
	
	//���߿� �����
	m_pCurWeapon->SetPos(GetPos());

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
		if (Key('A'))
		{
			pos.x -= m_fVelocity * fDT;
			StatuSet(GROUP_OBJECT_STATU::MOVE);
		}
		if (Key('D'))
		{
			pos.x += m_fVelocity * fDT;
			StatuSet(GROUP_OBJECT_STATU::MOVE);
		}

		if (Key('S'))
		{
	
		}

		if (KeyDown(VK_SPACE) || KeyDown('W')   // ����
			&& !StatuGet(GROUP_OBJECT_STATU::JUMP)
			&& StatuGet(GROUP_OBJECT_STATU::GROUND))
		{
			StatuSet(GROUP_OBJECT_STATU::JUMP);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}
		if (KeyDown(VK_LBUTTON)) //����
		{
			if (nullptr != m_pCurWeapon)
				PlayerAttack(playDir);

		}
		if (KeyDown('Q'))
		{


		}
	}
	SetPos(pos);

	//	StatuSet(GROUP_OBJECT_STATU::GROUND);
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


void CPlayer::OnCollisionEnter(CCollider* pOther)
{

	CGameObject* pOtherObj = pOther->GetObj();

	if (L"Weapon" == pOtherObj->GetName())
	{
		this->m_pCurWeapon = pOtherObj;
		((CWeapon*)m_pCurWeapon)->GetInfo();

	}

	
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
	else if (StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerRun", fPoint(50, 50), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	else if (!StatuGet(GROUP_OBJECT_STATU::GROUND) || StatuGet(GROUP_OBJECT_STATU::JUMP) || StatuGet(GROUP_OBJECT_STATU::FORCE))
	{
		GetAnimator()->Play(L"PlayerJump", fPoint(50, 50), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	StatuRemove(GROUP_OBJECT_STATU::MOVE);

}

void CPlayer::PlayerAttack(fPoint dir)
{
	m_playerAttack->SetPos(GetPos());
	m_playerAttack->SetOffSetPos(dir);
	CreateObj(m_playerAttack->Clone(), GROUP_GAMEOBJ::PLAYER_ATTACK);

}

void CPlayer::EatItem()
{

}

list<CItem*> CPlayer::GetInvetroy()
{
	return this->m_inventory;
}

CItem* CPlayer::GetCurItem(ITEM_PART type)
{
	return m_cCurItem[(UINT)type];
}
