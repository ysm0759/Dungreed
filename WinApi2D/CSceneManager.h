#pragma once

class CScene;
class CGameObject;

class CSceneManager
{
	SINGLETON(CSceneManager);
	
	friend class CEventManager;

private:
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];		// ÀüÃ¼ ¾À ¸ñ·Ï
	CScene* m_pCurScene;							// ÇöÀç ¾À


	vector<CGameObject*> m_arrRemain[(int)GROUP_GAMEOBJ::SIZE];


	void ChangeScene(GROUP_SCENE scene);			// ¾À ÀüÈ¯
	
	void DeleteGroup(GROUP_GAMEOBJ group);
	void DeleteAll();
public:
	void update();
	void render();
	void init();

	vector<CGameObject*>& GetRemain(GROUP_GAMEOBJ who);
	bool IsRemain(GROUP_GAMEOBJ who);
	CScene* GetCurScene();							//ÇöÀç ¾À ¹ÝÈ¯
};

