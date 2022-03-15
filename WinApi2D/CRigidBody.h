#pragma once



class CRigidBody
{
	friend class CGameObject;

	int m_iObjectStatu;
	float m_fGravity;
	float m_fVelocity;
	fVec2 m_fDashDir;
	CGameObject* m_pOwner;		// �浹ü�� ������ ���ӿ�����Ʈ�� �ּ�

	void Jump();
	void Gravity();
	void Dash();

public:
	CRigidBody();
	CRigidBody(const CRigidBody& other);
	~CRigidBody();

	void SetDashDir(fVec2 dashDir);
	void SetVelocity(float velocity);

	void update();


	void SetStatu(UINT bit);
	bool GetStatu(UINT bit);
	void RemoveStatu(UINT bit);
};

