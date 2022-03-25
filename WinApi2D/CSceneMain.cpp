#include "framework.h"
#include "CSceneMain.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CSound.h"
#include "CBackGround.h"
#include "CInOutButton.h"
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

	CreateBackGround();
	CreateButton();

	//CSoundManager::getInst()->AddSound(L"MainBGM", L"sound\\MainBGM.mp3", true);
	//CSoundManager::getInst()->Play(L"MainBGM");

	CSoundManager::getInst()->AddSound(L"VillageBGM", L"sound\\VillageBGM.mp3", true);
	CSoundManager::getInst()->Play(L"VillageBGM");


	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

}

void CSceneMain::Exit()
{
	DeleteAll();
	CSoundManager::getInst()->Stop(L"MainBGM");
	CCollisionManager::getInst()->Reset();
}

void CSceneMain::CreateBackGround()
{
	CBackGround* backGround1 = new CBackGround();
	backGround1->OnFix();
	backGround1->Load(L"BackGround1", L"texture\\Main\\BackGround1.png");
	backGround1->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround1, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround2 = new CBackGround();
	backGround2->OnAuto(50);
	backGround2->OnRepeat();
	backGround2->Load(L"BackGround2", L"texture\\Main\\BackGround2.png");
	backGround2->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround2, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround2Repeat = backGround2->Clone();
	backGround2Repeat->SetPos(fPoint(backGround2Repeat->GetPos().x + backGround2Repeat->GetScale().x, WINSIZEY / 2.f));
	AddObject(backGround2Repeat, GROUP_GAMEOBJ::BACK_GROUND);



	CBackGround* backGround3 = new CBackGround();
	backGround3->OnAuto(10);
	backGround3->OnRepeat(1000);
	backGround3->SetAlpha(0.2f);
	backGround3->Load(L"BackGround3", L"texture\\Main\\BackGround3.png");
	backGround3->SetPos(fPoint(WINSIZEX / 2.f + 150, WINSIZEY / 2.f));
	AddObject(backGround3, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround3Repeat = backGround3->Clone();
	backGround3Repeat->SetPos(fPoint(backGround3Repeat->GetScale().x + backGround3Repeat->GetPos().x + 150, WINSIZEY / 2.f));
	AddObject(backGround3Repeat, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* backGround4 = backGround3->Clone();
	backGround4->OnAuto(300);
	backGround4->SetAlpha(1.f);
	backGround4->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	AddObject(backGround4, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround4Repeat1 = backGround4->Clone();
	backGround4Repeat1->SetPos(fPoint(backGround4Repeat1->GetScale().x + backGround4Repeat1->GetPos().x + 150, WINSIZEY / 2.f));
	AddObject(backGround4Repeat1, GROUP_GAMEOBJ::BACK_GROUND);


	CBackGround* mainLogo = new CBackGround();
	mainLogo->OnFix();
	mainLogo->Load(L"Logo", L"texture\\Main\\Logo.png");
	mainLogo->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f - 100));
	AddObject(mainLogo, GROUP_GAMEOBJ::BACK_GROUND);






}


void GoToVillage(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::VILLAGE);
	//TODO: DataLoad Panel 보여주기
}

void GoToSetting(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TEST);
	//TODO: 세팅 scene보여주기
}

void GoToExit(DWORD_PTR, DWORD_PTR)
{
	PostQuitMessage(0);
}

void CSceneMain::CreateButton()
{
	//시작버튼
	CInOutButton* startButton = new CInOutButton;
	startButton->ButtonInLoadImg(L"PlayOn", L"texture\\Main\\PlayOn.png");
	startButton->ButtonOutLoadImg(L"PlayOff", L"texture\\Main\\PlayOff.png");
	startButton->SetPos(fPoint(WINSIZEX / 2.f - startButton->GetScale().x / 2, 400.f));
	startButton->SetClickedCallBack(GoToVillage, 0, 0);
	AddObject(startButton, GROUP_GAMEOBJ::UI);

	//세팅버튼
	CInOutButton* settingButton = new CInOutButton;
	settingButton->ButtonInLoadImg(L"OptionOn", L"texture\\Main\\OptionOn.png");
	settingButton->ButtonOutLoadImg(L"OptionOff", L"texture\\Main\\OptionOff.png");
	settingButton->SetPos(fPoint(WINSIZEX / 2.f - settingButton->GetScale().x / 2, 460.f));
	settingButton->SetClickedCallBack(GoToSetting, 0, 0);
	AddObject(settingButton, GROUP_GAMEOBJ::UI);

	//종료버튼
	CInOutButton* exitButton = new CInOutButton;
	exitButton->ButtonInLoadImg(L"ExitOn", L"texture\\Main\\ExitOn.png");
	exitButton->ButtonOutLoadImg(L"ExitOff", L"texture\\Main\\ExitOff.png");
	exitButton->SetPos(fPoint(WINSIZEX / 2.f - exitButton->GetScale().x / 2, 520.f));
	exitButton->SetClickedCallBack(GoToExit, 0, 0);
	AddObject(exitButton, GROUP_GAMEOBJ::UI);


}

