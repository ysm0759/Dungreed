#pragma once

class CGameObject;

struct tEvent
{
	TYPE_EVENT	eEven;		// �̺�Ʈ Ÿ��
	DWORD_PTR	lParam;		// �߰����� ����1
	DWORD_PTR	wParam;		// �߰����� ����2
};

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<tEvent> m_vecEvent;
	vector<CGameObject*> m_vecDead;

	void Execute(const tEvent& event);

public:
	void update();

	void AddEvent(const tEvent& event);
	void EventCreateObject(CGameObject* pObj, GROUP_GAMEOBJ group);
	void EventDeleteObject(CGameObject* pObj);
	void EventChangeScene(GROUP_SCENE scene);
};

