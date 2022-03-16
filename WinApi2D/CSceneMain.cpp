#include "framework.h"
#include "CSceneMain.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "Map_Start.h"
#include "CSound.h"
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
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(100, 100));
	pMonster->SetCenterPos(pMonster->GetPos());
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);

	CCameraManager::getInst()->SetTargetObj(pMonster);
}

void CSceneMain::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
