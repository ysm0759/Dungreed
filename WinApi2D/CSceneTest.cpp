#include "framework.h"
#include "CSceneTest.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CItem.h"
#include "CGameItem.h"
#include "CBackGround.h"
#include "CInOutButton.h"


#include "CSound.h"
#include "CD2DImage.h"

#include "CPlayerAttack.h"
#include "CWeapon.h"



CSceneTest::CSceneTest()
{
}

CSceneTest::~CSceneTest()
{

}

void CSceneTest::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}

	if (KeyDown('Z'))
	{
		CSoundManager::getInst()->AddSound(L"bgm", L"sound\\drumloop.wav", true);
		CSoundManager::getInst()->Play(L"bgm");
	}

	if (KeyDown('X'))
	{
		CSoundManager::getInst()->Stop(L"bgm");
	}
}

void CSceneTest::Enter()
{
	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start.tile";
	//LoadTile(path);
	// 
		// Player 추가
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);


	// Player 추가
	CGameObject* pMonster = new CMonster;
	pMonster->SetPos(fPoint(200, 600));
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	CGameObject* pMonsterClone = pMonster->Clone();
	pMonsterClone->SetPos(fPoint(200, 500));
	AddObject(pMonsterClone, GROUP_GAMEOBJ::MONSTER);


	CGameObject* pItem = new CGameItem(GROUP_GAMEITEM::GOLD_BIG);
	pItem->SetPos(fPoint(200, 200));
	AddObject(pItem, GROUP_GAMEOBJ::ITEM);


	CGameObject* pFariy = new CGameItem(GROUP_GAMEITEM::FAIRY_SMALL);
	pFariy->SetPos(fPoint(220, 200));
	AddObject(pFariy, GROUP_GAMEOBJ::ITEM);
	
	CGameObject* pFariy1 = new CGameItem(GROUP_GAMEITEM::FAIRY_MIDDLE);
	pFariy1->SetPos(fPoint(150, 200));
	AddObject(pFariy1, GROUP_GAMEOBJ::ITEM);

	CGameObject* pFariy2 = new CGameItem(GROUP_GAMEITEM::FAIRY_BIG);
	pFariy2->SetPos(fPoint(100, 200));
	AddObject(pFariy2, GROUP_GAMEOBJ::ITEM);
	
	
	CGameObject* pFariyClone = pFariy2->Clone();
	pFariyClone->SetPos(fPoint(100, 200));
	AddObject(pFariyClone, GROUP_GAMEOBJ::ITEM);


	//CGameObject* pWeapon = new CWeapon(ITEM_STATU::DROP , WEAPON_KIND::DEFAULT_SWORD , fPoint(100,100));
	//AddObject(pWeapon, GROUP_GAMEOBJ::ITEM);






	CCameraManager::getInst()->SetTargetObj(pPlayer);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::ITEM);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);
	
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::PLAYER_ATTACK);


}

void CSceneTest::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
