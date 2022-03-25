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
#include "CTile.h"
#include "CButtonUI.h"


#define DASHCREATETIME 1.2f
#define DASHVELOCITY 500.f
#define DASHTIME 0.125f

CPlayer::CPlayer()
{
	m_fVelocity = 100;
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
	m_iBottomCount = 0;
	//m_cCurItem.Accessories = nullptr;
	m_pCurWeapon = nullptr;
	m_pPlayerAttack = nullptr;
	for (int i = 0; i < (UINT)ITEM_PART::SIZE; i++)
	{
		m_cCurItem[i] = nullptr;
	}

	CreateCollider();
	GetCollider()->SetScale(fPoint(10.f, 10.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));



	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerStand", L"texture\\Player\\PlayerStand.png");
	GetAnimator()->CreateAnimation(L"PlayerStand", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 5);

	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerRun", L"texture\\Player\\PlayerRun.png");
	GetAnimator()->CreateAnimation(L"PlayerRun", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7);

	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\Player\\PlayerJump.png");
	GetAnimator()->CreateAnimation(L"PlayerJump", m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 1);

	CreateStatu();
	PrintInfo();
}

CPlayer::~CPlayer()
{
	delete m_pPlayerAttack;

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
	
	//나중에 지울것
	if (nullptr != m_cCurItem[(UINT)ITEM_PART::LeftWeapon])
		m_pCurWeapon = m_cCurItem[(UINT)ITEM_PART::LeftWeapon];
	//else if(nullptr == m_cCurItem[(UINT)ITEM_PART::RightWeapon])
	//	m_pCurWeapon = m_cCurItem[(UINT)ITEM_PART::LeftWeapon];
	//else
	//	m_inventory.push_back()




	if (nullptr != m_pCurWeapon)
		m_pCurWeapon->SetPos(GetPos());


	if (0 == m_iBottomCount)
	{
		StatuRemove(GROUP_OBJECT_STATU::GROUND);
	}
	else
	{
		wstring a = to_wstring(GetStatu()->GetUpDown());
		StatuRemove(GROUP_OBJECT_STATU::JUMP);
		StatuSet(GROUP_OBJECT_STATU::GROUND);
	}



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

		if ((KeyDown(VK_SPACE)  || KeyDown('W')) && StatuGet(GROUP_OBJECT_STATU::GROUND)  // 점프
			//&& !StatuGet(GROUP_OBJECT_STATU::JUMP)
			&& StatuGet(GROUP_OBJECT_STATU::GROUND))
		{
 			StatuSet(GROUP_OBJECT_STATU::JUMP);
			StatuRemove(GROUP_OBJECT_STATU::GROUND);
		}

		if (KeyDown(VK_LBUTTON)) //공격
		{
			if (nullptr != m_pCurWeapon)
				PlayerAttack(playDir);

		}
		if (KeyDown('Q'))
		{


		}
		if (KeyDown('R'))
		{
			ItemSwap();
		}
	}


	SetPos(pos);

	GetStatu()->update();


	// 캐릭터 상태에 따른 애니메이션
	StatuAnimator();

	//Statu 업데이트 중력, 대쉬 연산

	GetAnimator()->update();
}

void CPlayer::render()
{
	CRenderManager::getInst()->RenderText(to_wstring(m_iBottomCount),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x +200,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y ,
										  10 ,
										  50,
										  12,
										  RGB(0, 0, 0));

	CRenderManager::getInst()->RenderText(to_wstring(StatuGet(GROUP_OBJECT_STATU::JUMP)),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x +300 ,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y ,
										  10 ,
										  50,
										  12,
										  RGB(0, 0, 0));
	
	CRenderManager::getInst()->RenderText(to_wstring(StatuGet(GROUP_OBJECT_STATU::GROUND)),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x +400 ,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y ,
										  10 ,
										  50,
										  12,
										  RGB(0, 0, 0));

	
	CRenderManager::getInst()->RenderText(to_wstring(StatuGet(GROUP_OBJECT_STATU::FORCE)),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x +500 ,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y ,
										  10 ,
										  50,
										  12,
										  RGB(0, 0, 0));

	
	CRenderManager::getInst()->RenderText(to_wstring(m_cDashCount),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x +600 ,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y ,
										  10 ,
										  50,	
										  12,
										  RGB(0, 0, 0));

	CRenderManager::getInst()->RenderText(to_wstring(StatuGet(GROUP_OBJECT_STATU::DOWN)),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x + 700,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y,
										  10,
										  50,
										  12,
										  RGB(0, 0, 0));



	CRenderManager::getInst()->RenderText(to_wstring(GetStatu()->GetUpDown()),
										  CCameraManager::getInst()->GetRenderPos(GetPos()).x +1000 ,
										  CCameraManager::getInst()->GetRenderPos(GetPos()).y ,
										  10 ,
										  50,
										  12,
										  RGB(0, 0, 0));

	
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

	
	if (pOtherObj->GetName() == L"Tile") //TODO: 나중에 타일로 바꿀것
	{
		if (GROUP_TILE::GROUND == ((CTile*)pOtherObj)->GetGroup())
		{
			m_iBottomCount++;
		}

	}
}

void CPlayer::OnCollisionExit(CCollider* pOther)
{

	CGameObject* pOtherObj = pOther->GetObj();

	
	if (pOtherObj->GetName() == L"Tile") //TODO: 나중에 타일로 바꿀것
	{
		if (GROUP_TILE::GROUND == ((CTile*)pOtherObj)->GetGroup())
			m_iBottomCount--;
	}
}


void CPlayer::StatuAnimator()
{
	if (!StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerStand", fPoint(0, 0), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	else if (StatuGet(GROUP_OBJECT_STATU::MOVE) && StatuGet(GROUP_OBJECT_STATU::GROUND))
	{
		GetAnimator()->Play(L"PlayerRun", fPoint(0, 0), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	else if (!StatuGet(GROUP_OBJECT_STATU::GROUND) || StatuGet(GROUP_OBJECT_STATU::JUMP) || StatuGet(GROUP_OBJECT_STATU::FORCE))
	{
		GetAnimator()->Play(L"PlayerJump", fPoint(0, 0), StatuGet(GROUP_OBJECT_STATU::LOOK));
	}
	StatuRemove(GROUP_OBJECT_STATU::MOVE);
}

void CPlayer::PlayerAttack(fPoint dir)
{
	if (nullptr == m_pPlayerAttack)
	{
		m_pPlayerAttack = new CPlayerAttack((CWeapon*)m_pCurWeapon);
		m_pPlayerAttack->SetPos(GetPos());
		m_pPlayerAttack->SetOffSetPos(dir);
		CreateObj(m_pPlayerAttack->Clone(), GROUP_GAMEOBJ::PLAYER_ATTACK);
	}
	else
	{
		m_pPlayerAttack->SetPos(GetPos());
		m_pPlayerAttack->SetOffSetPos(dir);
		CreateObj(m_pPlayerAttack->Clone(), GROUP_GAMEOBJ::PLAYER_ATTACK);
	}

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


void CPlayer::ItemSwap()
{
	if (m_pPlayerAttack != nullptr)
	{
		delete m_pPlayerAttack;
		m_pPlayerAttack = nullptr;
	}
	if (m_pCurWeapon == m_cCurItem[(UINT)ITEM_PART::LeftWeapon])
	{
		m_pCurWeapon = m_cCurItem[(UINT)ITEM_PART::RightWeapon];
	}
	else
	{
		m_pCurWeapon = m_cCurItem[(UINT)ITEM_PART::LeftWeapon];
	}
}


void CPlayer::PrintInfo()
{


}