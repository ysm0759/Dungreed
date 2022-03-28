#pragma once

class CScene;
class CGameObject;

class CSceneManager
{
	SINGLETON(CSceneManager);
	
	friend class CEventManager;

private:
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];		// ��ü �� ���
	CScene* m_pCurScene;							// ���� ��


	vector<CGameObject*> m_arrRemain[(int)GROUP_GAMEOBJ::SIZE];


	void ChangeScene(GROUP_SCENE scene);			// �� ��ȯ
	
	void DeleteGroup(GROUP_GAMEOBJ group);
	void DeleteAll();
public:
	void update();
	void render();
	void init();

	vector<CGameObject*>& GetRemain(GROUP_GAMEOBJ who);
	bool IsRemain(GROUP_GAMEOBJ who);
	CScene* GetCurScene();							//���� �� ��ȯ
};

