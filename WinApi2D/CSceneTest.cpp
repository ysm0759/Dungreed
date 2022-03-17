#include "framework.h"
#include "CSceneTest.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Map_Start.h"

#include "CBackGround.h"
#include "CSound.h"
#include "CD2DImage.h"


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
		ChangeScn(GROUP_SCENE::MAIN);
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
	// Ÿ�� �ε�
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Start.tile";
	//LoadTile(path);

	// Player �߰�
	CGameObject* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	// Monster �߰� 
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(1100, 350));
	pMonster->SetCenterPos(pMonster->GetPos());
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);


	////TODO: ��������� �̻��� , �ִϸ��̼� �ȳ���
	//CGameObject* pOtherMonster = pMonster->Clone();//TODO: ���߿� �����
	//pOtherMonster->SetPos(fPoint(200, 500));
	//AddObject(pOtherMonster, GROUP_GAMEOBJ::MONSTER);


		// Monster �߰� 
	CBackGround* backGround1 = new CBackGround;
	backGround1->Load(L"BackGround_Start", L"texture\\Main\\BackGround1.png");
	backGround1->SetPos(fPoint(WINSIZEX / 2, WINSIZEX / 2));
	AddObject(backGround1, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround2 = new CBackGround(3 , true);
	backGround2->Load(L"BackGround_Start", L"texture\\Main\\BackGround2.png");
	backGround2->SetPos(fPoint(WINSIZEX / 2, WINSIZEX / 2));
	AddObject(backGround2, GROUP_GAMEOBJ::BACK_GROUND);

	CBackGround* backGround3 = new CBackGround(3 , true);
	backGround3->Load(L"BackGround_Start", L"texture\\Main\\BackGround3.png");
	backGround3->SetPos(fPoint(WINSIZEX / 2, WINSIZEX / 2));
	AddObject(backGround3, GROUP_GAMEOBJ::BACK_GROUND);



	Map_Start* map = new Map_Start;
	AddObject(map, GROUP_GAMEOBJ::MAP);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER_MISSILE, GROUP_GAMEOBJ::MONSTER);

	// Camera Look ����
	//CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CSceneTest::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
