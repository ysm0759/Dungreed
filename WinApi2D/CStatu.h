#pragma once



class CStatu
{
	friend class CGameObject;

	int m_iObjectStatu;
	float m_fGravity;
	float m_fForce;
	fVec2 m_fDir;
	CGameObject* m_pOwner;		// �浹ü�� ������ ���ӿ�����Ʈ�� �ּ�

	void Jump();
	void Gravity();
	void Fouce();
	void Dir();
public:
	CStatu();
	CStatu(const CStatu& other);
	~CStatu();

	void SetDashDir(fVec2 dashDir);
	void SetForce(float force);

	void update();


	void SetStatu(UINT bit);
	bool GetStatu(UINT bit);
	void RemoveStatu(UINT bit);
};

