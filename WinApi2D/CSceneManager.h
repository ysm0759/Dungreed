#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);
	
	friend class CEventManager;

private:
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];		// 전체 씬 목록
	CScene* m_pCurScene;							// 현재 씬

	void ChangeScene(GROUP_SCENE scene);			// 씬 전환
	

public:
	void update();
	void render();
	void init();

	CScene* GetCurScene();							//현재 씬 반환
};

