#pragma once



class CRigidBody
{
	friend class CGameObject;

	int m_iObjectStatu;
	float m_fGravity;
	CGameObject* m_pOwner;		// �浹ü�� ������ ���ӿ�����Ʈ�� �ּ�

	void Jump();
	void Gravity();
	void Dash();

public:
	CRigidBody();
	CRigidBody(const CRigidBody& other);
	~CRigidBody();


	void update();

	void SetStatu(UINT bit);
	bool GetStatu(UINT bit);
	void RemoveStatu(UINT bit);
};

