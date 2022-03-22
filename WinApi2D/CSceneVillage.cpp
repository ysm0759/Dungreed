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
#include "CCoin.h"



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
	//wstring path = CPathManager::getInst()->GetContentPath();
	//path += L"tile\\test.tile";
	//LoadTile(path);

	CreateBackGround();

	// Player Ãß°¡
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	


	CSoundManager::getInst()->AddSound(L"VillageBGM", L"sound\\VillageBGM.mp3", true);
	CSoundManager::getInst()->Play(L"VillageBGM");


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
	backGround1->SetBackScale(5);
	backGround1->Load(L"FixBackGround", L"texture\\Village\\FixBackGround.png");
	backGround1->SetPos(fPoint(WINSIZEX / 2.f - 200, WINSIZEY / 2.f+ 50));
	AddObject(backGround1, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround2 = new CBackGround();
	backGround2->OnFix();
	backGround2->OnDependOnObject(50);
	backGround2->SetBackScale(5);
	backGround2->SetPos(fPoint(-1500, 0));
	backGround2->Load(L"MiddleBackGround", L"texture\\Village\\MiddleBackGround.png");
	AddObject(backGround2, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround3 = new CBackGround();
	backGround3->OnFix();
	backGround3->OnDependOnObject(10);
	backGround3->SetBackScale(5);
	backGround3->Load(L"FrontBackGround", L"texture\\Village\\FrontBackGround.png");
	backGround3->SetPos(fPoint(-300, 200));
	AddObject(backGround3, GROUP_GAMEOBJ::BACK_GROUND);

}



