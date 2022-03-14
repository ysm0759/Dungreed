#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);
	
	friend class CEventManager;

private:
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];		// ��ü �� ���
	CScene* m_pCurScene;							// ���� ��

	void ChangeScene(GROUP_SCENE scene);			// �� ��ȯ
	

public:
	void update();
	void render();
	void init();

	CScene* GetCurScene();							//���� �� ��ȯ
};

