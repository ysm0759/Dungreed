#pragma once

class CCollider;

// ����ü : ���ο� ������ �������� ���� �����ּҸ� ���´�.
union COLLIDER_ID
{
	struct
	{
		UINT left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollisionManager
{
	SINGLETON(CCollisionManager);

private:
	/*
	* ���� �׷찣�� �浹�� ��Ʈ�� ���ؼ� ����
	* ex) m_arrCheck[GROUP_GAMEOBJ::PLAYER] = 0000 0000 0000 1100 �� ��
	* Player �׷��� 3, 2 ��° �׷��� Missile�� Monster�� �浹�Ѵ�.
	*/
	UINT m_arrCheck[(UINT)GROUP_GAMEOBJ::SIZE];		// �浹�ؾ��ϴ� �׷���� ���� �迭
	map<ULONGLONG, bool> m_mapCollInfo;				// �浹ü ���� ���� update �浹 ����

	void CollisionGroupUpdate(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);
	bool IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider);

public:
	void init();
	void update();

	void CheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);		// �׷찣 �浹 ����
	void UnCheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight);	// �׷찣 �浹 ����
	void Reset();
};

