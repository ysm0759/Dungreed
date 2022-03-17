#include "framework.h"
#include "CSceneMain.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSound.h"
#include "CBackGround.h"
#include "CInOutButton.h"
#include "CD2DImage.h"

void StartClick(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TEST);
}

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

	CBackGround* backGround1 = new CBackGround();
	backGround1->SetFix();
	backGround1->Load(L"BackGround1", L"texture\\Main\\BackGround1.png");
	backGround1->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround1, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround2 = new CBackGround();
	backGround2->SetAuto(50);
	backGround2->SetRepeat();
	backGround2->Load(L"BackGround2", L"texture\\Main\\BackGround2.png");
	backGround2->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround2, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround2Repeat = backGround2->Clone();
	backGround2Repeat->SetPos(fPoint(backGround2Repeat->GetPos().x + backGround2Repeat->GetScale().x, WINSIZEY / 2.f));
	AddObject(backGround2Repeat, GROUP_GAMEOBJ::BACK_GROUND);



	CBackGround* backGround3 = new CBackGround();
	backGround3->SetAuto(10);
	backGround3->SetRepeat(1000);
	backGround3->SetAlpha(0.2f);
	backGround3->Load(L"BackGround3", L"texture\\Main\\BackGround3.png");
	backGround3->SetPos(fPoint(WINSIZEX / 2.f + 150, WINSIZEY / 2.f));
	AddObject(backGround3, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround3Repeat = backGround3->Clone();
	backGround3Repeat->SetPos(fPoint(backGround3Repeat->GetScale().x + backGround3Repeat->GetPos().x + 150, WINSIZEY / 2.f));
	AddObject(backGround3Repeat, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround4 = backGround3->Clone();
	backGround4->SetAuto(300);
	backGround4->SetAlpha(1.f);
	backGround4->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround4, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround4Repeat1 = backGround4->Clone();
	backGround4Repeat1->SetPos(fPoint(backGround4Repeat1->GetScale().x + backGround4Repeat1->GetPos().x + 150, WINSIZEY / 2.f));
	AddObject(backGround4Repeat1, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* mainLogo = new CBackGround();
	mainLogo->SetFix();
	mainLogo->Load(L"Logo", L"texture\\Main\\Logo.png");
	mainLogo->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f - 100));
	AddObject(mainLogo, GROUP_GAMEOBJ::BACK_GROUND);




	// 3. 시작 버튼
	CInOutButton* startButton = new CInOutButton;
	startButton->ButtonInLoadImg(L"PlayOn", L"texture\\Main\\PlayOn.png");
	startButton->ButtonOutLoadImg(L"PlayOff", L"texture\\Main\\PlayOff.png");
	startButton->SetPos(fPoint(WINSIZEX / 2.f , 500.f));
	//startButton->SetScale(fPoint(100.f, 50.f));
	startButton->SetClickedCallBack(StartClick, 0, 0);
	AddObject(startButton, GROUP_GAMEOBJ::UI);



	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

}

void CSceneMain::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}

