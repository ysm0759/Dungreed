#include "framework.h"
#include "CSceneManager.h"

#include "CSceneTest.h"
#include "CScene_Tool.h"
#include "CSceneMain.h"
#include "CSceneVillage.h"

CSceneManager::CSceneManager()
{
	// 씬 목록 초기화
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		m_arrScene[i] = nullptr;
	}
	m_pCurScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	// 씬 목록 삭제
	for (int i = 0; i < (int)GROUP_SCENE::SIZE; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneManager::ChangeScene(GROUP_SCENE scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)scene];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneManager::render()
{
	m_pCurScene->render();
}

void CSceneManager::init()
{
	//TODO: Scene들 때려넣기

	m_arrScene[(size_t)GROUP_SCENE::TEST] = new CSceneTest;
	m_arrScene[(size_t)GROUP_SCENE::TEST]->SetName(L"CSceneTest");

	
	m_arrScene[(size_t)GROUP_SCENE::MAIN] = new CSceneMain;
	m_arrScene[(size_t)GROUP_SCENE::MAIN]->SetName(L"CSceneMain");

	
	m_arrScene[(size_t)GROUP_SCENE::VILLAGE] = new CSceneVillage;
	m_arrScene[(size_t)GROUP_SCENE::VILLAGE]->SetName(L"CSceneVillage");



	
	m_arrScene[(size_t)GROUP_SCENE::TOOL] = new CScene_Tool;
	m_arrScene[(size_t)GROUP_SCENE::TOOL]->SetName(L"Tool_Scene");

	m_pCurScene = m_arrScene[(size_t)GROUP_SCENE::MAIN];
	m_pCurScene->Enter();
}

CScene* CSceneManager::GetCurScene()
{
	return m_pCurScene;
}
