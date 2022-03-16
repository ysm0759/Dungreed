#include "framework.h"
#include "CSceneMain.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Map_Start.h"
#include "CSound.h"
#include "CBackGround.h"
#include "CD2DImage.h"

CSceneMain::CSceneMain()
{

}

CSceneMain::~CSceneMain()
{

}

void CSceneMain::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TEST);
	}

}

void CSceneMain::Enter()
{
	// Monster Ãß°¡ 
	CBackGround* backGround1 = new CBackGround;
	backGround1->Load(L"BackGround_Start", L"texture\\Main\\BackGround1.png");
	backGround1->SetPos(fPoint(WINSIZEX/2.f, WINSIZEY / 2.f));
	AddObject(backGround1, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround2 = new CBackGround(3);
	backGround2->Load(L"BackGround_Start", L"texture\\Main\\BackGround2.png");
	backGround2->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround2, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround3 = new CBackGround(3);
	backGround3->Load(L"BackGround_Start", L"texture\\Main\\BackGround3.png");
	backGround3->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround3, GROUP_GAMEOBJ::BACK_GROUND);



	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

}

void CSceneMain::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
