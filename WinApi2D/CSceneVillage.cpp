#include "framework.h"
#include "CSceneVillage.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSound.h"
#include "CBackGround.h"
#include "CInOutButton.h"
#include "CD2DImage.h"
#include "CItem.h"
#include "CGameItem.h"



CSceneVillage::CSceneVillage()
{

}

CSceneVillage::~CSceneVillage()
{

}

void CSceneVillage::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TEST);
	}

}

void CSceneVillage::Enter()
{

	CreateBackGround();

	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Village1.tile";
	LoadTile(path);
	// Player Ãß°¡
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);







	//CSoundManager::getInst()->AddSound(L"VillageBGM", L"sound\\VillageBGM.mp3", true);
	//CSoundManager::getInst()->Play(L"VillageBGM");

	CCameraManager::getInst()->SetTargetObj(pPlayer);


	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER_ATTACK);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);


	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::ITEM, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MONSTER, GROUP_GAMEOBJ::PLAYER_ATTACK);
}

void CSceneVillage::Exit()
{
	DeleteAll();
	CSoundManager::getInst()->Stop(L"VillageBGM");
	CCollisionManager::getInst()->Reset();
}

void CSceneVillage::CreateBackGround()
{


	CBackGround* backGround1 = new CBackGround();
	backGround1->OnFix();
	backGround1->SetBackScale(1);
	backGround1->Load(L"FixBackGround", L"texture\\Village\\FixBackGround.png");
	backGround1->SetPos(fPoint(WINSIZEX /ZOOM/ 2.f, WINSIZEY / ZOOM / 2.f));
	AddObject(backGround1, GROUP_GAMEOBJ::BACK_GROUND);


	float BackY = 320;

	CBackGround* backGround2 = new CBackGround();
	backGround2->OnFix();
	backGround2->OnDependOnObject(fPoint(5, 5));
	backGround2->SetBackScale(1);
	backGround2->SetPos(fPoint(WINSIZEX / ZOOM / 2.f - 320, WINSIZEY / ZOOM / 2.f));
	backGround2->Load(L"MiddleBackGround", L"texture\\Village\\MiddleBackGround.png");
	AddObject(backGround2, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround3 = new CBackGround();
	backGround3->OnFix();
	backGround3->OnDependOnObject(fPoint(1.2, 1.1));
	backGround3->SetBackScale(1);
	backGround3->Load(L"FrontBackGround", L"texture\\Village\\FrontBackGround.png");
	backGround3->SetPos(fPoint(320, BackY+32 ));
	AddObject(backGround3, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround4 = new CBackGround();
	backGround4->OnFix();
	backGround4->OnDependOnObject(fPoint(1, 1));
	backGround4->SetBackScale(100);
	backGround4->Load(L"None", L"texture\\tile\\None.png");
	backGround4->SetPos(fPoint(0, BackY + 160));
	AddObject(backGround4, GROUP_GAMEOBJ::BACK_GROUND);

	int FloorX = -163;
	CBackGround* backFloor = new CBackGround();
	backFloor->OnFix();
	backFloor->OnDependOnObject(fPoint(1, 1));
	backFloor->SetBackScale(1);
	backFloor->Load(L"Floor", L"texture\\Village\\Floor.png");
	backFloor->SetPos(fPoint(FloorX, BackY));
	AddObject(backFloor, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backFloorClone1 = backFloor->Clone();
	backFloorClone1->SetPos(fPoint(FloorX + 752, BackY));
	AddObject(backFloorClone1, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backFloorClone2 = backFloor->Clone();
	backFloorClone2->SetPos(fPoint(FloorX + 752 + 752, BackY));
	AddObject(backFloorClone2, GROUP_GAMEOBJ::BACK_GROUND);

}



